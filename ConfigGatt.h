#ifndef _CONFIG_GATT_H_
#define _CONFIG_GATT_H_

#include <stdint.h>
#include "HexUtils.h"
#include "BleSingleton.h"

class ConfigGatt {
public :

  enum CHAR_PROPERTY{
    READ = 0x02,
    WRITE_WITHOUT_RESPONSE = 0x04,
    WRITE = 0x08,
    NOTIFY = 0x10,
    INDICATE = 0x20
  };

  ConfigGatt();
	virtual ~ConfigGatt();
  
	bool clear(); //Clear all custom services and chars
	uint32_t addService(uint16_t uuid16); // Add a custom service || a list of existing services can be found at https://www.bluetooth.com/specifications/gatt/services
	uint32_t addService(uint8_t uuid128[]); // Add a custom service || firmware 0.6.6 or higher
	uint32_t addChar(uint16_t uuid16, CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value);  // Add a custom char to the last service added || a list of existing chars can be found at https://www.bluetooth.com/specifications/gatt/services
	uint32_t addChar(uint8_t uuid128[], CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value); // Add a custom char to the last service added || firmware 0.6.6 or higher
	
	char* getChar(uint8_t charID);
	bool setChar(uint8_t charID, char* val);
  
private :
  HexUtils hexUtils;

  uint32_t internalAddChar(CHAR_PROPERTY properties, uint8_t minlen, uint8_t maxlen, char* value);
  uint32_t internalReadId();
};
#endif /* _CONFIG_GATT_H_ */
