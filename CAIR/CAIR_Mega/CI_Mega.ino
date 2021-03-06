//Initiates Child Identification Module
//Provides functions to test Child Identification Module

//#define SERVOROTATEINCREMENTS 10
#define SCAN 6
#define STATUS 7
#define CHILDFOUND 8
int ciTestDelay = 500;
int child = 0;

void initiateBoardCOMS() {
  pinMode(SCAN, OUTPUT);
  setScan(0);
  pinMode(STATUS, INPUT);
  pinMode(CHILDFOUND, INPUT);
}

void setScan(int i) { //1 starts scanning
  digitalWrite(SCAN, i);
  if(i == 1){
    delay(50);
  }
}

int checkScanStatus(){
  return digitalRead(STATUS); 
}

int getCITestDelay() {
  return ciTestDelay;
}

void setCITestDelay(int i) {
  ciTestDelay = i;
}

void initiateCI() {
  //motorSetup(); //prepares servos NOT NEEDED
  //temperature sensor pin
  // thermalSensorSetup();//thermal sensor pin (I2C)
  powerDetectionSetup(); //power detection pin PUT THIS LAST
}

void activateCI() {
  if (checkCarVoltageStatus() == 0) { //if car is still off end process
    // Serial.println("Car is OFF");
    //   displayCarVoltage();
    //    delay(getCarVoltageReadDelay());
    return;
  }
  else {
    //Serial.println("Car has turned ON");
    while (checkCarVoltageStatus()) {
      //      Serial.println("Car is ON");
      //      displayCarVoltage();
      //      delay(getCarVoltageReadDelay());
    }
    Serial.println("Car has turned OFF");
    runCI();
  }
}

void runCI() { //monitor temperature and look for a child
  while (!checkTemperatureStatus()) {
    if (checkCarVoltageStatus()) { //if car turns back on while the temperature is being monitored, break entire child identification process
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

void checkForChild(){
  child = digitalRead(CHILDFOUND); 
}

void findChild() { //rotates servos to take measurements with thermal sensor
  //status from uno
  Serial.println("SCAN");
  setScan(1);
  while (1) {
    if (checkScanStatus() == 1) {
      setScan(0);
      checkForChild();
      break;
    }
  }
  Serial.println("DONE");
  getCoord();

  if (child == 1) {
    //CALL FOR HELP
    Serial.println("Person detected!");
    //    outputThermalData();
    //    delay(60000);
      printCoord(); //FOR MP3 DEMO ONLY
     contactEmerg();
  }
  else if (child == 0) {
    Serial.println("Person not detected!");
    //DO MOTION DETECTION GARBAGE
     printCoord(); //FOR MP3 DEMO ONLY
  }
}

void testCI() {
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
