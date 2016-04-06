//Initiates Child Identification Module
//Provides functions to test Child Identification Module

#define SERVOLOWERBOUND 30
#define SERVOHIGHERBOUND 135
//#define SERVOROTATEINCREMENTS 10
#define SCAN 2
#define STATUS 3
#define CHILDFOUND 4

void initiateBoardCOMS() {
  pinMode(SCAN, INPUT);
  pinMode(STATUS, OUTPUT);
  setStatus(0);
  pinMode(CHILDFOUND, OUTPUT);
  setChildFound(0);
}

void initiateCI() {
  //motorSetup(); //prepares servos NOT NEEDED
  //temperature sensor pin
  thermalSensorSetup();//thermal sensor pin (I2C)
  // powerDetectionSetup(); //power detection pin PUT THIS LAST
}

int checkScan(){
  return digitalRead(SCAN); 
}

void resetOutputs(){
  setStatus(0);
  setChildFound(0);
}

void setStatus(int i){
  digitalWrite(STATUS,i);
  delay(50); 
}

void setChildFound(int i){
  digitalWrite(CHILDFOUND,i);
  delay(50);
}

void findChild() { //rotates servos to take measurements with thermal sensor
  setStatus(0);
  setChildFound(0);
  Serial.println("SCANNING");
  for (int x = 0; x < (getThermalTiltBufferSize() / 4); x++) {
    moveTilt(120 - x * 30);
    for (int i = SERVOHIGHERBOUND; i >=  SERVOLOWERBOUND; i -= ((SERVOHIGHERBOUND - SERVOLOWERBOUND) / ((getThermalPanBufferSize() / 4) - 1))) {
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

  if (childSearch()) {
    //CALL FOR HELP
    Serial.println("Person detected!");
    setChildFound(1);

  }
  else {
    Serial.println("Person not detected!");
    setChildFound(0);
    //DO MOTION DETECTION GARBAGE
  }
  setStatus(1);
  delay(1500);
  resetOutputs();
}
