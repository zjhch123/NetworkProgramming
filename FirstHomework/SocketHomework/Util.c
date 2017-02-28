#include "Util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #define INVALID_LENGTH -5
// #define INVALID_CHARACTOR -4
// #define INVALID_STARTWITH -3
// #define ALREADY_USED -2
// #define FORMAT 1

int isDigit(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <='Z');
}

int isAlpha(char ch) {
	return ch >= '0' && ch <= '9';
}

int fileExsit(char* filename) {
	char dir[20];
	sprintf(dir, "user/%s", filename);
	FILE* file = fopen(dir, "r");
	if(file == NULL) {
		return 0;
	}
	close(file);
	return 1;
}

int checkUsername(char* username) {
	if(strlen(username) < 5 || strlen(username) >= 12) {
		return INVALID_LENGTH;
	}
	if(!isDigit(username[0])) {
		return INVALID_STARTWITH;
	}
	char* temp = username;
	while(*temp) {
		if(isDigit(*temp) || isAlpha(*temp)) {
			temp++;
		} else {
			return INVALID_CHARACTOR;
		}
	}
	if(fileExsit(username)) {
		return ALREADY_USED;
	}
	return FORMAT;
}

int checkPassword(char* password) {
	if(strlen(password) < 5) {
		return INVALID_LENGTH;
	}
	char* temp = password;
	while(*temp) {
		if(isDigit(*temp) || isAlpha(*temp)) {
			temp++;
		} else {
			return INVALID_CHARACTOR;
		}
	}
	return FORMAT;
}

int createUser(char* filename) {
	char dir[20];
	sprintf(dir, "user/%s", filename);
	FILE* file = fopen(dir, "w+");
	close(file);
	return 1;
}