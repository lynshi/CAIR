 //Main file

void setup() {
  initiateCI(); //set up pins for child identification PUT THIS LAST
  Serial.begin(9600);
}

void loop() {
  //testCI();
//  testReadVoltage();
//  delay(getCITestDelay());
  //only have two functions. House call functions within CI and CI within motion detection
  activateCI();
//  detectMotion();

//ALWAYS CONTINUALLY CHECK TO MAKE SURE CAR DOESN'T TURN BACK ON OR TEMPERATURE DROPS BELOW
}
