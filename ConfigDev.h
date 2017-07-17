#ifndef _CONFIG_DEV_H_
#define _CONFIG_DEV_H_

#include <Arduino.h>
#include "BleSingleton.h"

class ConfigDev {
public :
	ConfigDev(char* pwd="toto", char* device_name="BLE-Device-IoT");
	virtual ~ConfigDev();
  
	//State-related fctions
	bool start(bool verbose_mode = false, bool bloquant = true);
	void stop();
	bool isStarted();
	bool isConnected();
	bool isConnectable();
	bool isLoggedIn();
	bool isAdvertising();
	char* getDeviceName();
	void update();
	
	//Reset-related fctions
	void restart(bool blocking = true); // equivalent to a simple restart
	bool factoryReset(bool blocking = true); // hard reset, login needed

	//Advertising-related fctions
	bool startAdvertising(); // device become visible
	bool stopAdvertising(); // device become invisible
	
	//External connection related fctions
	void disconnect(); //Disconnect all external device if connected
	
	//Settings-related fctions
	bool login(char* pwd); //log in if pwd matches
	bool logout(); //log out, login needed
	bool setConfigPwd(char* pwd); //change pwd, login needed
	bool setDeviceName(char* name); // login needed
	bool setConnectable(bool b); //Wether or not the device should advertise itself as connectable
	
private :
	char* config_pwd;
	char* device_name;
	
	bool loggedIn = false;
	bool connectable;
	bool started;
	bool advertising;
};
#endif /* _CONFIG_DEV_H_ */
