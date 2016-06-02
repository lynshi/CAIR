//Controls servos
#include <Servo.h>

#define PANPIN 32
#define TILTPIN 30

Servo pan;
Servo tilt;
int panPos, tiltPos;
int spinDelay = 50;

//Gets and Sets
void delaySpin(){
  delay(getSpinDelay()); 
}

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

//Actually useful functions
void movePan(int pos){
  pan.attach(PANPIN);
  delay(100);
  setPanPos(pos);
  pan.write(getPanPos());
  Serial.println("movePan");
  Serial.println(pan.attached());
  Serial.println(pan.read());
  delay(500);
  pan.detach();
}

void moveTilt(int pos){
  tilt.attach(TILTPIN);
  delay(100);
  setTiltPos(pos);
  tilt.write(getTiltPos());
  Serial.println("moveTilt");
  Serial.println(tilt.attached());
  Serial.println(tilt.read());
  delay(500);
  tilt.detach();
}

//Testing
int testMotors() 
{   
  Serial.println("TestMotors");
  for(int i = 30; i < 150; i++){
    movePan(i);
//    Serial.print("Pan ");
//    Serial.println(i);
//    Serial.println(getPanPos());
    if(getPanPos() != i){
      Serial.println("Error: Pan motor at incorrect position!");
      Serial.print("Position should be: ");
      Serial.println(getPanPos());
      return 1;
    }
    moveTilt(i);
//    Serial.print("Tilt ");
//    Serial.println(i);
//    Serial.println(getTiltPos());
    if(getTiltPos() != i){
      Serial.println("Error: Tilt motor at incorrect position!");
      Serial.print("Position should be: ");
      Serial.println(getTiltPos());
      return 2;
    }  
    delaySpin();
  }
  for(int i = 150; i > 30; i--){
    movePan(i);
    if(getPanPos() != i){
      Serial.println("Error: Pan motor at incorrect position!");
      Serial.print("Position should be: ");
      Serial.println(getPanPos());
      return 1;
    }
    moveTilt(i);
    if(getTiltPos() != i){
      Serial.println("Error: Tilt motor at incorrect position!");
      Serial.print("Position should be: ");
      Serial.println(getTiltPos());
      return 2;
    }
    delaySpin();
  } 
  return 0;
}
