#include "ConfigDev.h"

ConfigDev::ConfigDev(char* pwd, char* name){
	loggedIn = false;
	connectable = true;
	started = false;
	advertising = false;
	
	config_pwd = (pwd!=NULL?pwd:"toto");
	device_name = (name==NULL?"BLE-Device-IoT":name);
}

ConfigDev::~ConfigDev(){
}
  
//State-related fctions
bool ConfigDev::start(bool verbose_mode, bool bloquant){
  Serial.println("initializing BLE lib");
	if(!started){
		started = BleSingleton::instance()->begin();
		
    Serial.println(F("started"));
	  if(!started){
      Serial.println(F("initialisation error"));
			return false;
		}
		
		login(config_pwd);
    setConnectable(this->connectable);
		setDeviceName(this->device_name);
    if(advertising)
      startAdvertising();
    else
      stopAdvertising();
    
    logout();
    /**/
    Serial.println(F("init complete"));
    return true;
	}else{
    Serial.println(F("init aborted : couldn't start Adafruit BLE lib"));
		return false;
	}
}

void ConfigDev::stop(){
	BleSingleton::instance()->end();
}

bool ConfigDev::isStarted(){
	return started;
}

bool ConfigDev::isConnected(){
	return BleSingleton::instance()->sendCommandCheckOK(F("AT+GAPGETCONN"));
}

bool ConfigDev::isConnectable(){
	return connectable;
}

bool ConfigDev::isLoggedIn(){
	return this->loggedIn;
}

bool ConfigDev::isAdvertising(){
	return this->advertising;
}

char* ConfigDev::getDeviceName(){
	return this->device_name;
}


void ConfigDev::update(){
	BleSingleton::instance()->update(200);
}

/* 
 * ------------------------------------------------------
 * Restart-related fctions
 * ------------------------------------------------------
 */
void ConfigDev::restart(bool blocking){ // equivalent to a simple restart
  logout();
	BleSingleton::instance()->reset(blocking);
}

bool ConfigDev::factoryReset(bool blocking){ // hard reset, login needed
   logout();
   return BleSingleton::instance()->factoryReset(blocking);
}
	
/* 
 * ------------------------------------------------------
 * Advertising-related fctions
 * ------------------------------------------------------
 */
bool ConfigDev::startAdvertising(){
	if(!advertising && loggedIn){
		bool state = BleSingleton::instance()->sendCommandCheckOK(F("AT+GAPSTARTADV"));
		if(state){
			advertising = true;
			return true;
		}
	}
	return false;
}

bool ConfigDev::stopAdvertising(){
	if(advertising && loggedIn){
		bool state =  BleSingleton::instance()->sendCommandCheckOK(F("AT+GAPSTOPADV"));
		if(state){
			advertising = false;
			return true;
		}
	}
	return false;
}

	
/* 
 * ------------------------------------------------------
 * External connection related fctions
 * ------------------------------------------------------
 */
void ConfigDev::disconnect(){ //Disconnect all external device if connected
	BleSingleton::instance()->disconnect();
}
	
/* 
 * ------------------------------------------------------
 * Settings-related fctions
 * ------------------------------------------------------
 */

bool ConfigDev::login(char* pwd){ //log in if pwd matches
	if(!loggedIn && strcmp(config_pwd, pwd)==0){
		loggedIn = true;
		return true;
	}
	return false;
}

bool ConfigDev::logout(){ //log out, login needed
	if(loggedIn){
		loggedIn = false;
		return true;
	}
	return false;
}


bool ConfigDev::setConfigPwd(char* pwd){ //change pwd, login needed
	if(loggedIn && pwd!=NULL){
		config_pwd = pwd;
		return true;
	}
	return false;
}


bool ConfigDev::setDeviceName(char* name){ // login needed
	if(loggedIn && strcmp(name,"")!=0){
    strcpy(device_name, name);
    BleSingleton::instance()->print("AT+GAPDEVNAME=");
    BleSingleton::instance()->println(name);
    return true;
	}
	return false;
}


bool ConfigDev::setConnectable(bool b){
	if(loggedIn){
		if(b && !connectable){
			BleSingleton::instance()->sendCommandCheckOK(F("AT+GAPCONNECTABLE=1"));
			connectable = true;
			return true;
		}else if(!b && connectable){
			BleSingleton::instance()->sendCommandCheckOK(F("AT+GAPCONNECTABLE=0"));
			connectable = false;
			return true;
		}
	}
	return false;
}

