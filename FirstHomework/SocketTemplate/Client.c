#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8021
#define MAX_LINE 1024
#define IP "127.0.0.1"

int main() {

    int socket_fd;
	char sendMsg[] = "Hello! Server\n";
    char recvMsg[MAX_LINE];
    struct sockaddr_in serverAddr;
	int recv_len;

    // init阶段
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1) {
        printf("open socket error\n");
        return -1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &serverAddr.sin_addr);

	// connect阶段
	if(connect(socket_fd, (struct socketaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
		printf("connect error!\n");
		return -1;
	}

	if((recv_len = recv(socket_fd, recvMsg, MAX_LINE, 0)) == -1) {
		printf("recv msg error!\n");
		return -1;
	}

	recvMsg[recv_len] = '\0';
	printf("recv msg: %s\n", recvMsg);

	if(send(socket_fd, sendMsg, strlen(sendMsg), 0) < 0) {
		printf("send msg error!\n");
		return -1;
	}
	printf("send msg to server: %s\n", sendMsg);

	// close阶段
	close(socket_fd);
	
	return 0;
}
