#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8021
#define MAX_LINE 1024

int main()
{
    int socket_fd, connect_fd;
    struct sockaddr_in serverAddr;
    char buf[MAX_LINE];
    char repeat[] = "Hello! Client\n";
    int recv_num;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);  
    if(socket_fd == -1) {
        printf("error to create socket! \n");
        return -1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));  
    serverAddr.sin_family = AF_INET;             
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serverAddr.sin_port = htons(PORT);           

    if(bind(socket_fd, (struct socketaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        printf("bind port to socket error! \n");
        return -1;
    }

    if(listen(socket_fd, 5) == -1) {
        printf("listen socket error! \n");
        return -1;
    }

    printf("listening...\n");

	while(1) {
    connect_fd = accept(socket_fd, NULL, NULL);

    if(connect_fd == -1) {
        printf("get socketer error!\n");
        return -1;
    }
    send(connect_fd, repeat, strlen(repeat), 0);

    recv_num = recv(connect_fd, buf, MAX_LINE, 0);
    buf[recv_num] = '\0';

    printf("recv_msg: %s\n", buf);


    // close
    close(connect_fd);
	}
    close(socket_fd);
    return 0;
}
