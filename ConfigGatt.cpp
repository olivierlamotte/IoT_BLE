#include "ConfigGatt.h"

ConfigGatt::ConfigGatt(){
  this->hexUtils = HexUtils();
}

ConfigGatt::~ConfigGatt(){
}
  
bool ConfigGatt::clear(){
	return BleSingleton::instance()->sendCommandCheckOK(F("AT+GATTCLEAR"));
}

uint32_t ConfigGatt::addService(uint16_t uuid16){
  BleSingleton::instance()->print("AT+GATTADDSERVICE=UUID=0x");
  BleSingleton::instance()->print(hexUtils.iTo2BHex(uuid16));  
  BleSingleton::instance()->println();
  return internalReadId();
}

uint32_t ConfigGatt::addService(uint8_t uuid128[]){
    BleSingleton::instance()->print("AT+GATTADDSERVICE=UUID128=0x");
	for(int i = 0; i<16; i++){
		if(i!=0)
			BleSingleton::instance()->print("-");
	    BleSingleton::instance()->print(hexUtils.iTo1BHex(uuid128[i]));
	}
  BleSingleton::instance()->println();
  return internalReadId();
}

uint32_t ConfigGatt::addChar(uint16_t uuid16, CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value){
	BleSingleton::instance()->print("AT+GATTADDCHAR=UUID=0x");
	BleSingleton::instance()->print(hexUtils.iTo2BHex(uuid16)); 
	return internalAddChar(properties, minlen, maxlen, value);
}

uint32_t ConfigGatt::addChar(uint8_t uuid128[], CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value){
	BleSingleton::instance()->print("AT+GATTADDCHAR=UUID128=0x");
	for(int i = 0; i<16; i++){
		if(i!=0)
			BleSingleton::instance()->print("-");
	    BleSingleton::instance()->print(hexUtils.iTo1BHex(uuid128[i]));
	}
  return internalAddChar(properties, minlen, maxlen, value);
}

uint32_t ConfigGatt::internalAddChar(CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value){
  if(properties!=NULL){
    BleSingleton::instance()->print(",PROPERTIES=0x");
    BleSingleton::instance()->print(hexUtils.iTo1BHex(properties));
  }
  if(minlen!=NULL){
    BleSingleton::instance()->print(",MIN_LEN=");
    BleSingleton::instance()->print(minlen);
  }
  if(maxlen!=NULL){
    BleSingleton::instance()->print(",MAX_LEN=");
    BleSingleton::instance()->print(maxlen);
  }
  if(value!=NULL){
    BleSingleton::instance()->print(",VALUE=");
    BleSingleton::instance()->print(value);
  }
  BleSingleton::instance()->println();
  return internalReadId();
}
	
char* ConfigGatt::getChar(uint8_t charID){
    BleSingleton::instance()->print("AT+GATTCHAR=");
    BleSingleton::instance()->println(charID);
	  if(BleSingleton::instance()->waitForOK()){
	    BleSingleton::instance()->readline();
      return BleSingleton::instance()->buffer;
	  }else{
      return -1;
    }
	
}

bool ConfigGatt::setChar(uint8_t charID, char* val){
    BleSingleton::instance()->print("AT+GATTCHAR=");
    BleSingleton::instance()->print(charID);
    BleSingleton::instance()->print(",");
    BleSingleton::instance()->print(val);
	  if(BleSingleton::instance()->waitForOK()){
	    BleSingleton::instance()->readline();
	    return (strcmp(BleSingleton::instance()->buffer,"OK") == 0);
	  }else{
      return -1;
    }
}

uint32_t ConfigGatt::internalReadId(){
  uint32_t val = BleSingleton::instance()->readline_parseInt();
  if(BleSingleton::instance()->waitForOK()){
    return val;
  }else{
    return -1;
  }
}
