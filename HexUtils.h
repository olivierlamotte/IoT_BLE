#ifndef _HEX_UTILS_H_
#define _HEX_UTILS_H_

#include <stdint.h>
#include <stdio.h>

#define TO_HEX(i) (i<=9? '0' + i : 'A'-10 + i)

class HexUtils {

public :
  HexUtils();
  virtual ~HexUtils();

	char* iTo1BHex(uint8_t nb);
	char* iTo2BHex(uint16_t nb);
 
};

#endif /*_HEX_UTILS_H_*/
