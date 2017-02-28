#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#include "message.h"

#define IP "127.0.0.1"
#define PORT 8002

int main() {
	int server_fd;
	struct sockaddr_in client_addr;
	char send_msg[MAX_MSG_LENGTH];
	int recv_length;

	message recv_msg;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(server_fd == -1) {
		printf("client socket create error!\n");
		return -1;
	}

	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_port = htons(PORT);
	client_addr.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &client_addr.sin_addr);

	if(connect(server_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
		printf("client socket connect error!\n");
		return -1;
	}

	// 接收欢迎信息
	recv_msg = recvMsg(server_fd);
	printf("welcome message: %s \n", recv_msg.body);


	// 接收”请输入用户名“
	recv_msg = recvMsg(server_fd);
	printf("%s\n", recv_msg.body);

	// 输入用户名并发送
	scanf("%s", send_msg);
	sendMsg(server_fd, send_msg);


	// 接收下一条信息。如果首字符为0，则说明是错误信息，需要进行处理
	recv_msg = recvMsg(server_fd);
	while(recv_msg.body[0] == '0') {
		memset(&send_msg, 0, sizeof(send_msg));
		printf("%s\n", recv_msg.body);
		scanf("%s", send_msg);
		sendMsg(server_fd, send_msg);
		recv_msg = recvMsg(server_fd);
	}

	// 接上， 如果不是错误信息，则输出”请输入密码“
	printf("%s\n", recv_msg.body);

	// 输入密码并发送
	scanf("%s", send_msg);
	sendMsg(server_fd, send_msg);

	// 接收下一条信息。如果首字符为0，则说明是错误信息，需要进行处理
	recv_msg = recvMsg(server_fd);
	while(recv_msg.body[0] == '0') {
		memset(&send_msg, 0, sizeof(send_msg));
		printf("%s\n", recv_msg.body);
		scanf("%s", send_msg);
		sendMsg(server_fd, send_msg);
		recv_msg = recvMsg(server_fd);
	}

	// 接上， 如果不是错误信息，则输出”结束信息“
	printf("%s\n", recv_msg.body);

	// 关闭socket
    close(server_fd);

    return 0;
}








