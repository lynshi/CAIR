//Main file

void setup() {
  Serial.begin(115200);
  //initiateCOM();
  initiateCI(); //set up pins for child identification PUT THIS LAST
}

void loop() {
  //only have two functions. House call functions within CI and CI within motion detection
  //activateCI();
  //detectMotion();
  checkTemperatureStatus();
  //placeCall();
  
//  findChild();
//  if(childSearch()){
//    Serial.println("Child found.");
//  }
//  else{
//    Serial.println("No child."); 
//  }
//  
//  outputThermalData();
  
  //delay(60000);
  delay(100);
  //ALWAYS CONTINUALLY CHECK TO MAKE SURE CAR DOESN'T TURN BACK ON OR TEMPERATURE DROPS BELOW
}
