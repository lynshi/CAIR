//Initiates Child Identification Module
//Provides functions to test Child Identification Module

#include "COM_Communications.h"

#define SERVOLOWERBOUND 30
#define SERVOHIGHERBOUND 135
//#define SERVOROTATEINCREMENTS 10

int ciTestDelay = 500;

int getCITestDelay(){
  return ciTestDelay;
}

void setCITestDelay(int i){
  ciTestDelay = i;
}

void initiateCI(){
  //motorSetup(); //prepares servos NOT NEEDED
  //temperature sensor pin
  thermalSensorSetup();//thermal sensor pin (I2C)
  powerDetectionSetup(); //power detection pin PUT THIS LAST
}

void activateCI(){
  if(checkCarVoltageStatus() == 0){ //if car is still off end process
    //Serial.println("Car is OFF");
//    displayCarVoltage();
//    delay(getCarVoltageReadDelay()); 
    return; 
  }
  else{
    //Serial.println("Car has turned ON");
    while(checkCarVoltageStatus()){
//      Serial.println("Car is ON");
//      displayCarVoltage(); 
//      delay(getCarVoltageReadDelay());
    }
    Serial.println("Car has turned OFF");
    runCI();
  }
}

void runCI(){ //monitor temperature and look for a child
  while(!checkTemperatureStatus()){
    if(checkCarVoltageStatus()){ //if car turns back on while the temperature is being monitored, break entire child identification process
      Serial.println("Car is back on");
      return;
    } 
    delay(getTempSenseDelay());
  }
  //Serial.println("Temperature has crossed 60 degree F threshold");
  //  temperature has now crossed threshold. Check for a child. CHECK FOR TEMPERATURE AGAIN BEFORE CALLING PARENT IF CHILD IS FOUND.
  findChild();
  //delay(10000);
}

void findChild(){ //rotates servos to take measurements with thermal sensor
  for(int x = 0; x < (getThermalTiltBufferSize() / 4); x++){
    moveTilt(120 - x * 30);
    for(int i = SERVOHIGHERBOUND; i >=  SERVOLOWERBOUND; i -= ((SERVOHIGHERBOUND - SERVOLOWERBOUND) / ((getThermalPanBufferSize() / 4) - 1))){
      setThermalTiltBufferPointer(x * 4);
      setThermalPanBufferPointer(((SERVOHIGHERBOUND - i) / ((SERVOHIGHERBOUND - SERVOLOWERBOUND) / ((getThermalPanBufferSize() / 4) - 1))) * 4);
      movePan(i);
      delay(getThermalReadDelay());
      readThermalSensor();
      Serial.print("Reading ");
      Serial.println(i);
    }  
  } 
  outputThermalData(); //outputs thermal data in tabular format; for MP2 demo purposes only
  //outputThermalDataP();
  
  getCoord();
  
  if(childSearch()){
    //CALL FOR HELP
    Serial.println("Person detected!");
//    outputThermalData();
//    delay(60000);  
    printCoord(); //FOR MP3 DEMO ONLY
    contactEmerg();
  }
  else{
    Serial.println("Person not detected!");
    //DO MOTION DETECTION GARBAGE
    printCoord(); //FOR MP3 DEMO ONLY
  }
}

void testCI(){
  Serial.println("CHILD IDENTIFICATION MODULE TEST PROGRAM");
  delay(getCITestDelay());
  //Serial.println("TESTING MOTORS");
  //delay(getCITestDelay());
  //if(testMotors() == 0){
  //  Serial.println("Motor testing successful!");
  //}
  //else{
  //  Serial.println("Motor testing unsuccessful :(");
  //}
  //delay(getCITestDelay());
  //
  //Serial.println("TESTING TEMPERATURE SENSOR");
  //delay(getCITestDelay());
  //if(testTempSensor() == 0){
  //  Serial.println("Temperature sensor is working :D");
  //}
  //else{
  //  Serial.println("Temperature sensor is not working :'("); 
  //}
  //delay(getCITestDelay());
  //Serial.println("TESTING POWER DETECTION");
  //delay(getCITestDelay());
  //if(testPowerDetection() == 0){
  //  Serial.println("Power detection is working :D");
  //}
  //else{
  //  Serial.println("Power detection is not working"); 
  //}
  //delay(getCITestDelay());
}
