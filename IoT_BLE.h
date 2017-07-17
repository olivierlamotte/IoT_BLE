#ifndef _IOT_BLE_H_
#define _IOT_BLE_H_

#include "ConfigDev.h"
#include "ConfigGatt.h"
#include "CommandParser.h"

#define PASSWORD "toto"
#define DEVICE_NAME "BLE-Device-IoT"
#define MAX_TIMEOUT_DECIS 150 //max timeout : 15.0 sec


class IoT_BLE {

public:
	IoT_BLE(){
		cfgGatt = ConfigGatt();
		cfgDev = ConfigDev(PASSWORD, DEVICE_NAME);
		cmdParser = CommandParser();
	};
	virtual ~IoT_BLE();

  bool start();
  
	void updateAndProcessCommand();
	void writeUART(char* str);
	char* readlineUART();
	char* readlineUART_timeout(int max_duration_decis);

	void restart();
	void echo(bool state);
	void info();
  
	void loginHandler();
	void logoutHandler();
	void logStatusHandler();
	void startAdvertisingHandler();
	void stopAdvertisingHandler();
	void advertiseStatusHandler();
	void resetHandler();
	void disconnectHandler();
	void changePasswordHandler();
	void allowConnectionHandler();
	void forbidConnectionHandler();
	void connectionStatusHandler();
	void changeDeviceNameHandler();
	void getDeviceNameHandler();
	void unknownCommandHandler();

	bool clear(); //Clear all custom services and chars
	uint32_t addService(uint16_t uuid16); // Add a custom service || a list of existing services can be found at https://www.bluetooth.com/specifications/gatt/services
	uint32_t addService(uint8_t uuid128[]); // Add a custom service || firmware 0.6.6 or higher
	uint32_t addChar(uint16_t uuid16, ConfigGatt::CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value);  // Add a custom char to the last service added || a list of existing chars can be found at https://www.bluetooth.com/specifications/gatt/characteristics
	uint32_t addChar(uint8_t uuid128[], ConfigGatt::CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value); // Add a custom char to the last service added || firmware 0.6.6 or higher
	
	char* getChar(uint8_t charID);
	bool setChar(uint8_t charID, char* val);

private: 

	ConfigGatt cfgGatt;
	ConfigDev cfgDev;
	CommandParser cmdParser;
	
	
	void internalHandleCommand();
};

#endif /* _IOT_BLE_H_ */
