//Initiates Child Identification Module
//Provides functions to test Child Identification Module

void initiateCI(){
  motorSetup(); //prepares servos
  //temperature sensor pin
  powerDetectionSetup(); //power detection pin
  //thermal sensor pin (I2C)
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
}

int getCITestDelay(){
  return ciTestDelay;
}

void setCITestDelay(int i){
  ciTestDelay = i;
}
