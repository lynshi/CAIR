//reads the voltage coming from the car battery to determine whether the car is on

#define CARPIN A1
#define RLARGE 302400
#define RSMALL 99000
#define VADJUST 0.40

double carVoltage;
bool carVoltageStatus;
int carVoltageReadDelay = 50;

//Most important function
bool checkCarVoltageStatus(){ //Return values: 1 car is on, 0 car is off.
  if(getCarVoltageStatus()){ //if 1, car was on. If 0, car was off.
    for(int i = 0; i < 5; i++){
      readCarVoltage();
      if(getCarVoltage() >= 14){
        return 1; 
      }
      delay(getCarVoltageReadDelay());
    }
    return 0; 
  }
  else{
    for(int i = 0; i < 5; i++){
      readCarVoltage();
      if(getCarVoltage() < 14){
        return 0; 
      }
      delay(getCarVoltageReadDelay());
    }
    return 1; 
  }
}

//Mildly useful functions
void readCarVoltage(){
  setCarVoltage(analogRead(CARPIN));
//  Serial.println("ANALOGREAD: "); //testing
//  Serial.println(getCarVoltage()); 
//  delay(1000);
//  setCarVoltage(map(carVoltage, 0, 1023, 0, 5000)); //map uses integer values. 3 decimal points are needed so the mapped-to value is scaled up by 1000
//  Serial.println("MAP: "); //testing
//  Serial.println(getCarVoltage()); 
//  delay(1000);
//  setCarVoltage((getCarVoltage()/(double)1000)*(double)4); //scales voltage back down (e.g. 3125 -> 3.125) and converts to voltage at car battery (0-20)
  setCarVoltage((map(getCarVoltage(), 0, 1023, 0, 5000)/(double)1000)*(double)(RLARGE + RSMALL)/(double)RSMALL + VADJUST); //scales voltage back down (e.g. 3125 -> 3.125) and converts to voltage at car battery (0-20). Also acounts for error)
}

void powerDetectionSetup(){
  pinMode(CARPIN, INPUT);
  setCarVoltageStatus(0); 
}

//Gets and sets
double getCarVoltage(){
  return carVoltage; 
}

void setCarVoltage(double i){
  carVoltage = i; 
}

void setCarVoltageReadDelay(int i){
  carVoltageReadDelay = i; 
}

int getCarVoltageReadDelay(){
  return carVoltageReadDelay; 
}

void setCarVoltageStatus(bool s){
  carVoltageStatus = s;
}

bool getCarVoltageStatus(){
  return carVoltageStatus; 
}

//Testing
int testPowerDetection(){
  while(!checkCarVoltageStatus()){ //waiting for car to turn on
    Serial.print("Car is OFF and voltage is currently: ");
    Serial.print(getCarVoltage());
    Serial.println("V");   
  }
  
  while(checkCarVoltageStatus()){ //waiting for car to turn off
    Serial.print("Car is ON and voltage is currently: ");
    Serial.print(getCarVoltage());
    Serial.println("V");
  }
  
  Serial.print("Car is OFF and voltage is currently: ");
  Serial.print(getCarVoltage());
  Serial.println("V");
  
  return 0;
}

void testReadVoltage(){
  readCarVoltage();
//  Serial.print("Divided Voltage is currently: ");
//  Serial.print(getCarVoltage()*(double)RSMALL/(double)(RSMALL+RLARGE));
  Serial.print("Voltage is currently: ");
  Serial.print(getCarVoltage());
  Serial.println("V");
}
