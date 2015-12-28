//Initiates Child Identification Module
//Provides functions to test Child Identification Module

void activateCI(){
  bool temp;
  temp = getCarVoltageStatus();
  if(temp == 0){ //if car is still off end process
    return; 
  }
  controlPower(checkCarVoltageStatus());
  if(temp != getCarVoltageStatus()){ //if car was on and turns off start child identification
    runCI();
  }
}

void runCI(){ //monitor temperature and look for a child
  while(!checkTemperature()){
    if(checkCarVoltageStatus()){ //if car turns back on while the temperature is being monitored, break entire child identification process
      return;
    } 
  }
  
//  temperature has now crossed threshold. Check for a child.
}

void initiateCI(){
  motorSetup(); //prepares servos
  //temperature sensor pin
  //thermal sensor pin (I2C)
  powerDetectionSetup(); //power detection pin PUT THIS LAST
}

int ciTestDelay = 500;

void testCI(){
  Serial.println("CHILD IDENTIFICATION MODULE TEST PROGRAM");
  delay(getCITestDelay());
  
  Serial.println("TESTING MOTORS");
  delay(getCITestDelay());
  if(testMotors() == 0){
    Serial.println("Motor testing successful!");
  }
  else{
    Serial.println("Motor testing unsuccessful :(");
  }
  delay(getCITestDelay());
  
  Serial.println("TESTING TEMPERATURE SENSOR");
  delay(getCITestDelay());
  if(testTempSensor() == 0){
    Serial.println("Temperature sensor is working :D");
  }
  else{
    Serial.println("Temperature sensor is not working :'("); 
  }
  delay(getCITestDelay());
  
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
