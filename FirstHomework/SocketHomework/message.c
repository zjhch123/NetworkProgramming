#include <string.h>
#include <stdlib.h>
#include "message.h"

message recvMsg(int from) {
	char message_body[MAX_MSG_LENGTH];
	int message_length = recv(from, message_body, MAX_MSG_LENGTH, 0);

	message msg;

	if(message_length != -1) {
		msg.code = 1;
		msg.length = message_length;
		message_body[message_length] = '\0';
		strcpy(msg.body, message_body);
	} else {
		msg.code = -1;
	}
	return msg;
}

int sendMsg(int to, char *message) {
	return send(to, message, strlen(message), 0);
}