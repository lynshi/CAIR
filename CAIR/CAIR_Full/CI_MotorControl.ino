#include <Servo.h>

Servo pan;
Servo tilt;

int panPos, tiltPos;
int spinDelay = 500;
int panPin = 9;
int tiltPin = 10;

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
  pan.attach(getPanPin());
  tilt.attach(getTiltPin());
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

int getPanPin(){
  return panPin; 
}

void setPanPin(int i){
  panPin = i; 
}

int getTiltPin(){
  return tiltPin; 
}

void setTiltPin(int i){
  tiltPin = i; 
}



//Testing
void testMotors() 
{   
  for(int i = 30; i < 150; i++){
    movePan(i);
    moveTilt(i);
    delaySpin();
  }
  
  for(int i = 150; i > 30; i--){
    movePan(i);
    moveTilt(i);
    delaySpin();
  }
}
