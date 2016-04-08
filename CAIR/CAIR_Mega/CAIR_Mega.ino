//Main file
//#include <Adafruit_FONA.h>
//#include <PCM.h>
//#include <stdlib.h>
//#include <SoftwareSerial.h>

void setup() {
  Serial.begin(115200);
  initiateCOM();
  
  initiateBoardCOMS();
  initiateCI(); //set up pins for child identification PUT THIS LAST
}

void loop() {
  //only have two functions. House call functions within CI and CI within motion detection
  //activateCI();
  //detectMotion();
  //getCoord();
  //printCoord();
  //contactEmerg();
  //placeCall();
  findChild();

  
  delay(60000);
  //ALWAYS CONTINUALLY CHECK TO MAKE SURE CAR DOESN'T TURN BACK ON OR TEMPERATURE DROPS BELOW
}
