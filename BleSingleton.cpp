#include "BleSingleton.h"

static Adafruit_BluefruitLE_SPI * BleSingleton::ptr_instance = 0;

BleSingleton::~BleSingleton(){}

Adafruit_BluefruitLE_SPI* BleSingleton::instance(){
		if(BleSingleton::ptr_instance==NULL)
			BleSingleton::ptr_instance = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
		
		return BleSingleton::ptr_instance;
}
