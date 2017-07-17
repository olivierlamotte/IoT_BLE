#include "CommandParser.h"

CommandParser::CommandParser(){}

CommandParser::~CommandParser(){}

COMMAND CommandParser::parseCommand(char* str){
	if(strcmp(str, "login") == 0){
		return LOGIN;
	}else if(strcmp(str, "logout") == 0){
		return LOGOUT;
	}else if(strcmp(str, "setadvon") == 0){
		return START_ADVERTISE;
	}else if(strcmp(str, "setadvoff") == 0){
		return STOP_ADVERTISE;
	}else if(strcmp(str, "reset") == 0){
		return RESET;
	}else if(strcmp(str, "disconnect") == 0){
		return DISCONNECT;
	}else if(strcmp(str, "setpwd") == 0){
		return CHANGE_PASSWORD;
	}else if(strcmp(str, "setconon") == 0){
		return ALLOW_CONNECTION;
	}else if(strcmp(str, "setconoff") == 0){
		return FORBID_CONNECTION;
	}else if(strcmp(str, "getcon") == 0){
		return GET_CONNECTION_STATUS;
	}else if(strcmp(str, "getadv") == 0){
		return GET_ADVERTISE_STATUS;
	}else if(strcmp(str, "getlog") == 0){
		return GET_LOG_STATUS;
	}else if(strcmp(str, "getdevname") == 0){
		return GET_DEVICE_NAME;
	}else if(strcmp(str, "setdevname") == 0){
		return CHANGE_DEVICE_NAME;
	}else{
		return UNKNOWN_COMMAND;
	}
}
