#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#define PORT 4396
#define IP "127.0.0.1"
#define MAX_LENGTH 1024

int main() {
	int connect_fd;
	char recv_msg[MAX_LENGTH];
	char repeat[] = "Hello!Server";
	struct sockaddr_in serverAddr;
	int recv_length;

	connect_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(connect_fd == -1) {
		printf("create socket error!\n");
		return -1;
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	inet_pton(AF_INET, IP, &serverAddr.sin_addr);

	if(connect(connect_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
		printf("connect socket error!\n");
		return -1;
	}


	if((recv_length = recv(connect_fd, recv_msg, MAX_LENGTH, 0)) < 0) {
		printf("recv msg error!\n");
		return -1;
	}
	recv_msg[recv_length] = '\0';
	printf("recv: %s\n", recv_msg);

	if(send(connect_fd, repeat, strlen(repeat), 0) < 0) {
		printf("send msg error!\n");
		return -1;
	}

	close(connect_fd);

	return 0;
}




