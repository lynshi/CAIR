//Searches for motion in the car

#define MOTIONINPUT1 47
#define MOTIONINPUT2 49
#define MOTIONLED 38

int val1 = 0, val2 = 0;                    // variable for reading the pin status
 
void motionDetectionSetup() {
  pinMode(MOTIONINPUT1, INPUT);     // declare sensor as input
  pinMode(MOTIONINPUT2, INPUT);
  pinMode(MOTIONLED, OUTPUT);
  controlMotionLED(0);
}

void controlMotionLED(int state){ //1 is on 0 is off
  digitalWrite(MOTIONLED, state);
}
 
bool detectMotion(){
  //return 0; //TEMP NOT DOING THIS
  controlMotionLED(1);
  for(int i = 0; i < 5; i++){
    val1 = digitalRead(MOTIONINPUT1);  // read input value
    val2 = digitalRead(MOTIONINPUT2);
    if (val1 == LOW && val2 == LOW) {            // HIGH means motion detected
      return 0;
    }
    delay(60);
  }
  Serial.println("Motion detected!");
  return 1;
}
