#ifndef _BLE_SINGLETON_H_
#define _BLE_SINGLETON_H_

#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
  #include <SoftwareSerial.h>
#endif

#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>

#define BLUEFRUIT_SPI_CS 8
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST              6    // Optional but recommended, set to -1 if unused

class BleSingleton{
	
public:
	BleSingleton(){}
	virtual ~BleSingleton();

	static Adafruit_BluefruitLE_SPI* instance();
private:	

  // Singleton instance 
  static Adafruit_BluefruitLE_SPI * ptr_instance;
};

#endif /*_BLE_SINGLETON_H_*/
