//Main file

void setup() {
  Serial.begin(115200);
  //initiateCOM();
  initiateBoardCOMS();
  initiateCI(); //set up pins for child identification PUT THIS LAST
}

void loop() {
  if(checkScan())
  {
    Serial.println("DO STUFF");
    findChild();
  }
}
