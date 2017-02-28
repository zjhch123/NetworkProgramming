#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 4396
#define MAX_LENGTH 1024

int main() {
	int socket_fd, client_fd;
	struct sockaddr_in serverAddr;
	char repeat[] = "Hello!Client";
	char buf[MAX_LENGTH];
	int recv_length;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd == -1) {
		printf("open socket error!\n");
		return -1;
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(socket_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
		printf("socket bind error!\n");
		return -1;
	}

	listen(socket_fd, 5);

	printf("listen...\n");

	while(1) {
		client_fd = accept(socket_fd, NULL, NULL);
		
		if(client_fd == -1) {
			printf("get connect error!\n");
			continue;
		}

		if(send(client_fd, repeat, strlen(repeat), 0) < 0) {
			printf("send msg error!\n");
		}

		if((recv_length = recv(client_fd, buf, MAX_LENGTH, 0)) < 0) {
			printf("recv msg error!\n");
		}

		buf[recv_length] = '\0';

		printf("recv msg: %s\n", buf);

		close(client_fd);
	}

	close(socket_fd);

	return 0;
}












