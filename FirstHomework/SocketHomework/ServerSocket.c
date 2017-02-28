#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "message.h"
#include "Util.h"

#define PORT 8002
#define MAX_MSG_LENGTH 1024

char welcome[] = WELCOME_MSG;
char username_msg[] = USERNAME_MSG;
char username_msg_invalid_charactor[] = USERNAME_MSG_INVALID_CHARACTOR;
char username_msg_invalid_length[] = USERNAME_MSG_INVALID_LENGTH;
char username_msg_invalid_startwith[] = USERNAME_MSG_INVALID_STARTWITH;
char username_msg_repeat[] = USERNAME_MSG_REPEAT;
char password_msg[] = PASSWORD_MSG;
char password_msg_invalid_length[] = PASSWORD_MSG_INVALID_LENGTH;
char password_msg_invalid_charactor[] = PASSWORD_MSG_INVALID_CHARACTOR;
char ok_msg[] = OK_MSG;

int main() {
	int server_fd;
	int client_fd;
	
	int recv_length;

	struct sockaddr_in server_addr;
	message recv_msg;


	char* body;
	char username[20];
	char password[20];

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == -1) {
		printf("server socket create error!\n");
		return -1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
		printf("bind socket error!\n");
		return -1;
	}

	listen(server_fd, 5);

	printf("listening...\n");

	while(1) {
		client_fd = accept(server_fd, NULL, NULL);

		if(client_fd == -1) {
			printf("get connect error!\n");
			continue;
		}

		// 发送欢迎信息
		sendMsg(client_fd, welcome);
		sleep(1);

		// 发送”请输入用户名“
		sendMsg(client_fd, username_msg);
		
		// 接收用户名
		recv_msg = recvMsg(client_fd);
		body = recv_msg.body;

		// 检测用户名
		int checkUsn = checkUsername(body);

		while(checkUsn != FORMAT) {
			// 发送错误信息
			switch(checkUsn) {
				case INVALID_LENGTH:
					sendMsg(client_fd, username_msg_invalid_length);
					break;
				case INVALID_CHARACTOR:
					sendMsg(client_fd, username_msg_invalid_charactor);
					break;
				case INVALID_STARTWITH:
					sendMsg(client_fd, username_msg_invalid_startwith);
					break;
				case ALREADY_USED:
					sendMsg(client_fd, username_msg_repeat);
					break;
				default:
					checkUsn = INVALID_LENGTH;
			}
			// 接收重新提交的用户名
			recv_msg = recvMsg(client_fd);
			body = recv_msg.body;
			checkUsn = checkUsername(body);
		}

		strcpy(username, body);
		// 发送”请输入密码“
		sendMsg(client_fd, password_msg);

		// 接收密码
		recv_msg = recvMsg(client_fd);
		body = recv_msg.body;

		int checkPwd = checkPassword(body);

		while(checkPwd != FORMAT) {
			// 发送错误信息
			switch(checkPwd) {
				case INVALID_LENGTH:
					sendMsg(client_fd, password_msg_invalid_length);
					break;
				case INVALID_CHARACTOR:
					sendMsg(client_fd, password_msg_invalid_charactor);
					break;
				default:
					checkPwd = INVALID_LENGTH;
			}
			// 接收重新提交的密码
			recv_msg = recvMsg(client_fd);
			body = recv_msg.body;
			checkPwd = checkPassword(body);
		}
		strcpy(password, body);
		// 发送”OK“
		sendMsg(client_fd, ok_msg);
		close(client_fd);
		printf("*****************\n");
		printf("register:\n");
		printf("username: %s\n", username);
		printf("password: %s\n", password);
		printf("*****************\n\n");
		createUser(username);
	}
	
	close(server_fd);

	return 0;
}


