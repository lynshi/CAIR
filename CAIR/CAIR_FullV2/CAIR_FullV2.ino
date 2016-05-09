void setup() {
  Serial.begin(115200);
  Serial.println("Please press # key to begin");  
  //Keypad entry
  while(readKeypad() != '#'){ //pressing # activates the program
    ;  
  }
  
  getPhoneNumber();
  
  Serial.println("The program will now begin!");
  delay(1000);
  
  initiateAudio();
  initiateCOM();
  initiateCI(); //PUT LAST
}

void loop() {
  activateCI();  
  //motion detection
}
