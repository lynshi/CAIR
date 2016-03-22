//Uses Omron Thermal Sensor to detect heat and humans
#include <Wire.h>
//1 GND Ground
//2 VCC Power source (5V +/-10%)
//3 SDA I2C(5V) Data line
//4 SCL I2C(5V) Clock line
#define THERMALPANBUFFERSIZE 16
#define THERMALTILTBUFFERSIZE 12
#define HOTTHRESHOLD 270

int thermalReadDelay = 500;
int thermalPanBufferPointer;
int thermalTiltBufferPointer;
int thermalBuffer[THERMALTILTBUFFERSIZE][THERMALPANBUFFERSIZE];

void thermalSensorSetup(){
  Wire.begin(); 
  setThermalPanBufferPointer(0);
  setThermalTiltBufferPointer(0);
}

int childSearch(){ //looks for a child; 1 if there is a child, 0 if not
  setThermalPanBufferPointer(0);
  setThermalTiltBufferPointer(0);
  int hotPixels = 0;
  while(1){
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(getThermalBuffer(i + getThermalTiltBufferPointer(),j + getThermalPanBufferPointer()) >= HOTTHRESHOLD){
          hotPixels++;  
        }
      }  
    }
    if(hotPixels >= 5){ //so I can see what's going on
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          setThermalBuffer(0,i + getThermalTiltBufferPointer(),j + getThermalPanBufferPointer());
        }  
      }
      return 1;
    }
    else{
      hotPixels = 0;
      if(getThermalPanBufferPointer() == 14){
        setThermalPanBufferPointer(0);
        setThermalTiltBufferPointer(getThermalTiltBufferPointer() + 1);  
      }
      else{
        setThermalPanBufferPointer(getThermalPanBufferPointer() + 1);  
      }
      if(getThermalTiltBufferPointer() == 11){
        break;  
      }
    }
  }
  return 0;
}
 
 void setThermalTiltBufferPointer(int i){
  thermalTiltBufferPointer = i;
}

int getThermalTiltBufferPointer(){
  return thermalTiltBufferPointer; 
}

int getThermalTiltBufferSize(){
  return THERMALTILTBUFFERSIZE; 
}

int getThermalPanBufferSize(){
  return THERMALPANBUFFERSIZE; 
}
int getThermalPanBufferPointer(){
  return thermalPanBufferPointer;
}

void setThermalPanBufferPointer(int i){
  thermalPanBufferPointer = i; 
}

int getThermalReadDelay(){
  return thermalReadDelay; 
}

void setThermalReadDelay(int d){
   thermalReadDelay = d; 
}

int getThermalBuffer(int i, int j){
  if((j >= THERMALPANBUFFERSIZE) || (j < 0)){
    Serial.println("Thermal Buffer Pan Access Error");
    return 0; 
  }
  if((i >= THERMALTILTBUFFERSIZE) || (i < 0)){
    Serial.println("Thermal Buffer Tilt Access Error");
    return 0; 
  }
  return thermalBuffer[i][j]; 
}

void setThermalBuffer(int val, int i, int j){
  if((j >= THERMALPANBUFFERSIZE) || (j < 0)){
    Serial.println("Error setting thermal buffer pan data");
    return; 
  }
  if((i >= THERMALTILTBUFFERSIZE) || (i < 0)){
    Serial.println("Error setting thermal buffer tilt data");
    return; 
  }
  thermalBuffer[i][j] = val; 
}
 
void readThermalSensor()
{
  int count=0;
  int reading = 0;
  int buff[16];
  Wire.beginTransmission(0x0a);
  Wire.write(byte(0x4c));      // sets register pointer to echo #1 register (0x02)
  if(Wire.endTransmission(false) != 0){      // stop transmitting
    Serial.println("BROKEN!!!");
    delay(10000);
  }  
  // step 4: request reading from sensor
  Wire.requestFrom(0x0a, 34);    // request 2 bytes from slave device #112
  // step 5: receive reading from sensor
  while(count<34){
    if(2 <= Wire.available()){   // if two bytes were received
      reading = Wire.read();  // receive high byte (overwrites previous reading) 
      reading += Wire.read()<<8;    
      if(count != 0){
         buff[15 - ((count - 2) / 2)] = reading;
      }           
      //Serial.print("Count: "); 
      //Serial.println(count);
      //Serial.print("Pan Pointer: ");
      //Serial.println(getThermalPanBufferPointer());
      //Serial.print("Tilt Pointer: ");
      //Serial.println(getThermalTiltBufferPointer());
      count+=2;
    }
  }
 // Serial.println("count done");
  for(int i = 0; i < 16; i++){
    if((i % 4) == 0 && (i != 0)){
      setThermalTiltBufferPointer(1 + getThermalTiltBufferPointer());
    }
    setThermalBuffer(buff[i], getThermalTiltBufferPointer(), getThermalPanBufferPointer() + (i % 4));
  }
}

void outputThermalData(){
  for(int x = 0; x < THERMALTILTBUFFERSIZE; x++){
    if(x % 4 == 0){
      for(int i = 0; i < THERMALPANBUFFERSIZE * 6 - 1; i++){
        Serial.print("_");
      }
      Serial.println("__________");
    }
    Serial.print("| ");
    for(int i = 0; i < THERMALPANBUFFERSIZE; i++){
      Serial.print((double)getThermalBuffer(x, i) / 10.0);
      if(i % 4 != 3){
        Serial.print(" ");
      }
      else if (i % 4 == 3 && i != THERMALPANBUFFERSIZE - 1){
        Serial.print(" | ");  
      }
    }
    Serial.println(" |");
  }  
  for(int i = 0; i < THERMALPANBUFFERSIZE * 6 - 1; i++){
    Serial.print("_");
  }
  Serial.println("__________");
}

void outputThermalDataP(){
  for(int x = 0; x < THERMALTILTBUFFERSIZE; x++){
    for(int i = 0; i < THERMALPANBUFFERSIZE; i++){
      Serial.print(getThermalBuffer(x, i));
      Serial.print(" ");
    }
  }
  Serial.println(".");
}
