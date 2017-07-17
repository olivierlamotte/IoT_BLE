#include "IoT_BLE.h"

IoT_BLE::~IoT_BLE(){}

bool IoT_BLE::start(){
  return cfgDev.start();
}

void IoT_BLE::updateAndProcessCommand(){
	BleSingleton::instance()->update();
  
	if(BleSingleton::instance()->isConnected()){
		while(readlineUART()){
			internalHandleCommand();
		}
	}else{
		delay(500);
	}
}

void IoT_BLE::writeUART(char* str){
    BleSingleton::instance()->print("AT+BLEUARTTX=");
    BleSingleton::instance()->println(str);
}

char* IoT_BLE::readlineUART(){    
	// Check for incoming characters from Bluefruit
    BleSingleton::instance()->println("AT+BLEUARTRX");
    BleSingleton::instance()->readline();
    
    if (strcmp(BleSingleton::instance()->buffer, "OK") == 0) {
      // no data
      return NULL;
    }
    BleSingleton::instance()->waitForOK();
    return BleSingleton::instance()->buffer;
}
char* IoT_BLE::readlineUART_timeout(int max_timeout_decis){
	int timeout = 0;
	do{
		if(timeout>0){
			delay(100);
		}
		timeout++;
		BleSingleton::instance()->println("AT+BLEUARTRX");
		BleSingleton::instance()->readline();
	}while(strcmp(BleSingleton::instance()->buffer, "OK") == 0 && timeout<max_timeout_decis);
   
	if(timeout>=max_timeout_decis){
		return NULL;
	}
	BleSingleton::instance()->waitForOK();
	return BleSingleton::instance()->buffer;
}

void IoT_BLE::internalHandleCommand(){
	switch(cmdParser.parseCommand(BleSingleton::instance()->buffer)){
		case LOGIN:
			loginHandler();
			break;
		case LOGOUT:
			logoutHandler();
			break;
		case GET_LOG_STATUS:
			logStatusHandler();
			break;
		case START_ADVERTISE:
			startAdvertisingHandler();
			break;
		case STOP_ADVERTISE:
			stopAdvertisingHandler();
			break;
		case GET_ADVERTISE_STATUS:
			advertiseStatusHandler();
			break;
		case RESET:
			resetHandler();
			break;
		case DISCONNECT:
			disconnectHandler();
			break;
		case CHANGE_PASSWORD:
			changePasswordHandler();
			break;
		case ALLOW_CONNECTION:
			allowConnectionHandler();
			break;
		case FORBID_CONNECTION:
			forbidConnectionHandler();
			break;
		case GET_CONNECTION_STATUS:
			connectionStatusHandler();
			break;
		case CHANGE_DEVICE_NAME:
			changeDeviceNameHandler();
			break;
		case GET_DEVICE_NAME:
			getDeviceNameHandler();
			break;
		default:
			unknownCommandHandler();
			break;
	}
}

void IoT_BLE::loginHandler(){
	if(!cfgDev.isLoggedIn()){
		writeUART("Enter admin password : ");
		if(readlineUART_timeout(MAX_TIMEOUT_DECIS)){
		bool state = cfgDev.login(BleSingleton::instance()->buffer);
		if(state)
			writeUART("Logged in successfully : now in admin mode");
		else
			writeUART("Error during identification process");
		}else{
			writeUART("Timeout");
		}
	}else{
		writeUART("Already logged in");
	}
}

void IoT_BLE::logoutHandler(){
	writeUART("Exiting admin mode");
	cfgDev.logout();
}

void IoT_BLE::logStatusHandler(){
	writeUART((cfgDev.isLoggedIn()?"Admin mode active":"Admin mode inactive"));
}

void IoT_BLE::startAdvertisingHandler(){
	writeUART("Starting advertising...");
	if(cfgDev.isLoggedIn()){
		cfgDev.startAdvertising();
	}else{
		writeUART("Please enter admin mode first");
	}
}

void IoT_BLE::stopAdvertisingHandler(){
	writeUART("Stopping advertising...");
	if(cfgDev.isLoggedIn()){
		cfgDev.stopAdvertising();
	}else{
		writeUART("Please enter admin mode first");
	}
}

void IoT_BLE::advertiseStatusHandler(){
	writeUART((cfgDev.isAdvertising()?"Device advertising":"Device not advertising"));
}

void IoT_BLE::resetHandler(){
	writeUART("Restarting...");
	cfgDev.restart();
}

void IoT_BLE::disconnectHandler(){
	writeUART("Disconnecting all devices...");
	cfgDev.disconnect();
}

void IoT_BLE::changePasswordHandler(){
	if(cfgDev.isLoggedIn()){
		writeUART("Enter new password : ");
		if(readlineUART_timeout(MAX_TIMEOUT_DECIS)){
			bool state = cfgDev.setConfigPwd(BleSingleton::instance()->buffer);
			if(state){
				writeUART("Password changed");
			}else{
				writeUART("Error");
			}
		}else{
			writeUART("Timeout");
		}
	}else{
		writeUART("Please enter admin mode first");
	}
}

void IoT_BLE::allowConnectionHandler(){
	if(cfgDev.isLoggedIn()){
		writeUART("Device now allow connections");
		cfgDev.setConnectable(true);
	}else{
		writeUART("Please enter admin mode first");
	}
}

void IoT_BLE::forbidConnectionHandler(){
	if(cfgDev.isLoggedIn()){
		writeUART("Device now refuse connections");
		cfgDev.setConnectable(false);
	}else{
		writeUART("Please enter admin mode first");
	}
}

void IoT_BLE::connectionStatusHandler(){
	writeUART((cfgDev.isConnectable()?"Device allowing connections":"Device refusing connections"));
}

void IoT_BLE::changeDeviceNameHandler(){
	if(cfgDev.isLoggedIn()){
		writeUART("Enter new device name : ");
		if(readlineUART_timeout(MAX_TIMEOUT_DECIS)){
			bool state = cfgDev.setDeviceName(BleSingleton::instance()->buffer);
			if(state){
			  writeUART("Device name changed");
			}else{
			  writeUART("Error");
			}
		}else{
			writeUART("Eimeout");
		}
	}else{
		writeUART("Please enter admin mode first");
	}
}

void IoT_BLE::getDeviceNameHandler(){
	writeUART(cfgDev.getDeviceName());
}

void IoT_BLE::unknownCommandHandler(){
	writeUART("cmd invalide");
}

bool IoT_BLE::clear(){
	return cfgGatt.clear();
}

uint32_t IoT_BLE::addService(uint16_t uuid16){
	return cfgGatt.addService(uuid16);
}

uint32_t IoT_BLE::addService(uint8_t uuid128[]){
	return cfgGatt.addService(uuid128);
}

uint32_t IoT_BLE::addChar(uint16_t uuid16, ConfigGatt::CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value){
	return cfgGatt.addChar(uuid16, properties, minlen, maxlen, value);
}

uint32_t IoT_BLE::addChar(uint8_t uuid128[], ConfigGatt::CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value){
	return cfgGatt.addChar(uuid128, properties, minlen, maxlen, value);
}

char* IoT_BLE::getChar(uint8_t charID){
	return cfgGatt.getChar(charID);
}

bool IoT_BLE::setChar(uint8_t charID, char* val){
	return cfgGatt.setChar(charID, val);
}


void IoT_BLE::restart(){
  resetHandler();
}
void IoT_BLE::echo(bool state){
  BleSingleton::instance()->echo(state);
}
void IoT_BLE::info(){
  BleSingleton::instance()->info();
}

