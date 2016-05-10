//Searches for motion in the car

#define MOTIONINPUT 2;
#define MOTIONLED 3;

int val = 0;                    // variable for reading the pin status
 
motionDetectionSetup() {
  pinMode(MOTIONINPUT, INPUT);     // declare sensor as input
  pinMode(MOTIONLED, OUTPUT);
  controlMotionLED(0);
}

void controlMotionLED(int state){ //1 is on 0 is off
  digitalWrite(MOTIONLED, state);
}
 
bool detectMotion(){
  controlMotionLED(1);
  val = digitalRead(MOTIONINPUT);  // read input value
  if (val == HIGH) {            // HIGH means motion detected
    Serial.println("Motion detected!");
    return 1;
  }
  else{
    return 0; 
  }
}
