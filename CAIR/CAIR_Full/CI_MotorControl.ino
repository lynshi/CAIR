//Controls servos

#include <Servo.h>

Servo pan;
Servo tilt;

int panPos, tiltPos;
int spinDelay = 50;
#define PANPIN 9
#define TILTPIN 10

//Actually useful functions
void movePan(int pos){
  setPanPos(pos);
  pan.write(getPanPos());
}

void moveTilt(int pos){
  setTiltPos(pos);
  tilt.write(getTiltPos()); 
}

void delaySpin(){
  delay(getSpinDelay()); 
}

void motorSetup(){
  pan.attach(PANPIN);
  tilt.attach(TILTPIN);
}

//Gets and Sets
int getPanPos(){
  return panPos; 
}

void setPanPos(int i){
  panPos = i; 
}

int getTiltPos(){
  return tiltPos; 
}

void setTiltPos(int i){
  tiltPos = i; 
}

int getSpinDelay(){
  return spinDelay; 
}

void setSpinDelay(int i){
  spinDelay = i; 
}

//Testing
int testMotors() 
{   
  for(int i = 30; i < 150; i++){
    movePan(i);
    if(getPanPos() != i){
      Serial.println("Error: Pan motor at incorrect position!");
      return 1;
    }
    moveTilt(i);
    if(getTiltPos() != i){
      Serial.println("Error: Tilt motor at incorrect position!");
      return 2;
    }
    delaySpin();
  }
  
  for(int i = 150; i > 30; i--){
    movePan(i);
    if(getPanPos() != i){
      Serial.println("Error: Pan motor at incorrect position!");
      return 1;
    }
    moveTilt(i);
    if(getTiltPos() != i){
      Serial.println("Error: Tilt motor at incorrect position!");
      return 2;
    }
    delaySpin();
  }
  
  return 0;
}

