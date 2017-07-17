#include "HexUtils.h"

HexUtils::HexUtils(){}

HexUtils::~HexUtils(){}

char* HexUtils::iTo1BHex(uint8_t nb){
	if(nb<= 0xFF){
		char reply[3];
		sprintf(reply, "%02X", nb);
		return reply;
	}
	return NULL;
}

char* HexUtils::iTo2BHex(uint16_t nb){
	if(nb<= 0xFFFF){
		char reply[5];
		sprintf(reply, "%04X", nb);
		return reply;
	}
	return NULL;
}
