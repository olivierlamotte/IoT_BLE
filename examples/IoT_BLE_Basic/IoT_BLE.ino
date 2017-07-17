#include "IoT_BLE.h"

IoT_BLE iotble;

int32_t servid_1000;
int32_t servid_2000;
int32_t charid_1001;
int32_t charid_2001;

void setup() {

   while(!Serial)
    delay(500);

   Serial.begin(115200);
   Serial.println("Serial started");
    
  
  iotble.start();
  iotble.clear();

  //Définition du service uuid=0x1000 et d'une char associé à lui (0x1001)
  servid_1000 = iotble.addService(0x1000);
  Serial.print(F("Service added -> ID : "));
  Serial.println(servid_1000);
  charid_1001 = iotble.addChar(0x1001,ConfigGatt::CHAR_PROPERTY::READ,4,4,NULL);
  Serial.print(F("Char added -> ID : "));
  Serial.println(charid_1001);

  //Définition du service uuid=0x2000 et d'une char associé à lui (0x2001)
  servid_2000 = iotble.addService(0x2000);
  Serial.print(F("Service added -> ID : "));
  Serial.println(servid_2000);
  charid_2001 = iotble.addChar(0x2001,ConfigGatt::CHAR_PROPERTY::READ,4,4,NULL);
  Serial.print(F("Char added -> ID : "));
  Serial.println(charid_2001);

  iotble.restart(); //Redémarage nécessaire pour la prise en compte des modifs (clear + ajout services et chars)
  iotble.echo(false);
  iotble.info(); //Affichage des infos 
  /**/

  Serial.println("Ended");
}

void loop() {
  iotble.updateAndProcessCommand();
}
