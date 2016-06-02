#define SERVOLOWERBOUND 45
#define SERVOHIGHERBOUND 135
//#define SERVOROTATEINCREMENTS 10
#define EMERGDELAY 12000 //wait two minutes between calling parent and emergency
int ciTestDelay = 500;

void initiateCI() {
  thermalSensorSetup();
  motionDetectionSetup();
  thermistorSetup();
  powerDetectionSetup(); //PUT LAST
}
int getCITestDelay() {
  return ciTestDelay;
}

void setCITestDelay(int i) {
  ciTestDelay = i;
}
void activateCI() {
  if (checkCarVoltageStatus() == 0) { //if car is still off end process
      Serial.println("Car is OFF");
      displayCarVoltage();
      delay(getCarVoltageReadDelay());
    return;
  }
  else {
    //Serial.println("Car has turned ON");
    while (checkCarVoltageStatus()) {
      Serial.println("Car is ON");
      displayCarVoltage();
      delay(getCarVoltageReadDelay());
    }
    Serial.println("Car has turned OFF");
    runCI();
  }
}
void runCI() { //monitor temperature and look for a child
  controlMotionLED(0);
  while (!checkTemperatureStatus()) { //MAY GET STUCK HERE IF BROUGHT IN BY MOTION DETECTION
    if (checkCarVoltageStatus()) { //if car turns back on while the temperature is being monitored, break entire child identification process
      Serial.println("Car is back on");
      return;
    }
    delay(getTempSenseDelay());
  }

  //Serial.println("Temperature has crossed 60 degree F threshold");
  //  temperature has now crossed threshold. Check for a child. CHECK FOR TEMPERATURE AGAIN BEFORE CALLING PARENT IF CHILD IS FOUND.
  if (findChild()) {
    contact();
  }
  else {
    Serial.println("Person not detected!");
  }
  //delay(10000);
}

bool findChild() //1 child found 0 no child
{
  Serial.println("SCANNING");
  for (int x = 0; x < (getThermalTiltBufferSize() / 4); x++) {
    moveTilt(120 - x * 30);
    for (int i = SERVOHIGHERBOUND; i >=  SERVOLOWERBOUND; i -= ((SERVOHIGHERBOUND - SERVOLOWERBOUND) / ((getThermalPanBufferSize() / 4) - 1))) {
      setThermalTiltBufferPointer(x * 4);
      setThermalPanBufferPointer(((SERVOHIGHERBOUND - i) / ((SERVOHIGHERBOUND - SERVOLOWERBOUND) / ((getThermalPanBufferSize() / 4) - 1))) * 4);
      movePan(i);
      delay(getThermalReadDelay());
      readThermalSensor();
    }
  }
  outputThermalData(); //outputs thermal data in tabular format; for MP2 demo purposes only
  //outputThermalDataP();
  getCoord();
  return childSearch();
}

void contact() { //CALL FOR HELP
  Serial.println("Person detected!");
  contactParent();
  delay(EMERGDELAY);
  if(checkTemperatureStatus()){
    if (detectMotion) {
      contactEmerg();
    }
    else {
      if(findChild()){
        contactEmerg(); 
      }
    }    
  }
}
