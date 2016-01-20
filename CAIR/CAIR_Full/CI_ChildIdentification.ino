//Initiates Child Identification Module
//Provides functions to test Child Identification Module

#define SERVOLOWERBOUND 30
#define SERVOHIGHERBOUND 150
//#define SERVOROTATEINCREMENTS 10

void activateCI(){
  if(checkCarVoltageStatus() == 0){ //if car is still off end process
    Serial.println("Car is OFF");
    displayCarVoltage();
    delay(getCarVoltageReadDelay()); 
    return; 
  }
  else{
    while(checkCarVoltageStatus()){
      Serial.println("Car is ON");
      displayCarVoltage(); 
      delay(getCarVoltageReadDelay());
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
  
  Serial.println("Temperature has crossed 60 degree F threshold");
  //  temperature has now crossed threshold. Check for a child. CHECK FOR TEMPERATURE AGAIN BEFORE CALLING PARENT IF CHILD IS FOUND.
  
  findChild();
  //delay(10000);
}

void findChild(){ //rotates servos to take measurements with thermal sensor
  movePan(SERVOLOWERBOUND);
  moveTilt(SERVOLOWERBOUND);
  delay(getThermalReadDelay());
  readThermalSensor();
  
  for(int x = 0; x < getThermalTiltBufferSize(); x++){
    for(int i = SERVOLOWERBOUND; i <= SERVOHIGHERBOUND; i += 120 / (getThermalPanBufferSize() / 17)){
      delay(getThermalReadDelay());
      readThermalSensor();
    }  
    setThermalTiltBufferPointer(getThermalTiltBufferPointer() + 1);
    setThermalPanBufferPointer(0);
  }
}

void initiateCI(){
  motorSetup(); //prepares servos
  //temperature sensor pin
  thermalSensorSetup();//thermal sensor pin (I2C)
  powerDetectionSetup(); //power detection pin PUT THIS LAST
}

int ciTestDelay = 500;

void testCI(){
  Serial.println("CHILD IDENTIFICATION MODULE TEST PROGRAM");
  delay(getCITestDelay());
  
//  Serial.println("TESTING MOTORS");
//  delay(getCITestDelay());
//  if(testMotors() == 0){
//    Serial.println("Motor testing successful!");
//  }
//  else{
//    Serial.println("Motor testing unsuccessful :(");
//  }
//  delay(getCITestDelay());
//  
//  Serial.println("TESTING TEMPERATURE SENSOR");
//  delay(getCITestDelay());
//  if(testTempSensor() == 0){
//    Serial.println("Temperature sensor is working :D");
//  }
//  else{
//    Serial.println("Temperature sensor is not working :'("); 
//  }
//  delay(getCITestDelay());
  
//  Serial.println("TESTING POWER DETECTION");
//  delay(getCITestDelay());
//  if(testPowerDetection() == 0){
//    Serial.println("Power detection is working :D");
//  }
//  else{
//    Serial.println("Power detection is not working"); 
//  }
//  delay(getCITestDelay());
}

int getCITestDelay(){
  return ciTestDelay;
}

void setCITestDelay(int i){
  ciTestDelay = i;
}
