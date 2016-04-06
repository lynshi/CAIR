//Main file


void setup() {
  Serial.begin(115200);
  //initiateCOM();
  initiateBoardCOMS();
  initiateCI(); //set up pins for child identification PUT THIS LAST
}

void loop() {
  Serial.println("LOOP");
  if(digitalRead(getScanPin()))
  {
    Serial.println("DO STUFF");
    findChild();
  }
  //ALWAYS CONTINUALLY CHECK TO MAKE SURE CAR DOESN'T TURN BACK ON OR TEMPERATURE DROPS BELOW
}
