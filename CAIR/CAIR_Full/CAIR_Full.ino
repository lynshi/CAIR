//Main file

void setup() {
  initiateCI(); //set up pins for child identification
  Serial.begin(9600);
}

void loop() {
  //testCI();
  testReadVoltage();
  delay(getCITestDelay());
}
