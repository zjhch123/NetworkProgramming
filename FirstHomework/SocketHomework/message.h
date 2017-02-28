#define MAX_MSG_LENGTH 1024

#define WELCOME_MSG "Hello! Client"
#define USERNAME_MSG "Please input your username:"
#define USERNAME_MSG_INVALID_CHARACTOR "0Error! Result: Username invalid charactor\nPlease input your username again:"
#define USERNAME_MSG_INVALID_LENGTH "0Error! Result: Username invalid length\nPlease input your username again:"
#define USERNAME_MSG_INVALID_STARTWITH "0Error! Result: Username invalid start with\nPlease input your username again:"
#define USERNAME_MSG_REPEAT "0Error! Result: Username already used\nPlease input your username again:"
#define PASSWORD_MSG "Please input your password:"
#define PASSWORD_MSG_INVALID_LENGTH "0Error! Result: Password invalid length\nPlease input your password again:"
#define PASSWORD_MSG_INVALID_CHARACTOR "0Error! Result: Password invalid charactor\nPlease input your password again:"
#define OK_MSG "OK! Welcome!"


typedef struct msg {
	int code;
	char body[MAX_MSG_LENGTH];
	int length;
} message;

message recvMsg(int);
int sendMsg(int, char*);