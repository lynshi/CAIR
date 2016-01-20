//Uses Omron Thermal Sensor to detect heat and humans

#include <Wire.h>

//1 GND Ground
//2 VCC Power source (5V +/-10%)
//3 SDA I2C(5V) Data line
//4 SCL I2C(5V) Clock line

#define THERMALPANBUFFERSIZE 68
#define THERMALTILTBUFFERSIZE 3

int thermalReadDelay = 500;
int thermalPanBufferPointer;
int thermalTiltBufferPointer;

double thermalBuffer[THERMALTILTBUFFERSIZE][THERMALPANBUFFERSIZE];
 
void thermalSensorSetup(){
  Wire.begin(); 
  thermalPanBufferPointer = 0;
  thermalTiltBufferPointer = 0;
}
 
void readThermalSensor()
 
{
 
  // step 3: instruct sensor to return a particular echo reading
 
  Wire.beginTransmission(0x0a);
  //Serial.println("Break1"); 
  Wire.write(byte(0x4c));      // sets register pointer to echo #1 register (0x02)
 
  if(Wire.endTransmission(false) != 0){      // stop transmitting
    Serial.println("BROKEN!!!");
    delay(10000);
  }
  
  //Serial.println("Break2");
 
  // step 4: request reading from sensor
 
  Wire.requestFrom(0x0a, 34);    // request 2 bytes from slave device #112
 
  //Serial.println("Break3"); 
  // step 5: receive reading from sensor
 
  int count=0;
  int reading = 0;
 
  while(count<34){
  //Serial.print("Count NOT AVAILABLE: "); 
  //Serial.println(count);
  if(2 <= Wire.available())    // if two bytes were received
    {
   
      reading = Wire.read();  // receive high byte (overwrites previous reading)
   
      reading += Wire.read()<<8;
      
      setThermalBuffer(reading, getThermalTiltBufferPointer(), (count/2) + (getThermalPanBufferPointer() * 17));
   
      //Serial.print(reading);   // print the reading
   
      //Serial.print(" ");
   
      count+=2;
      //Serial.print("Count: "); 
      //Serial.println(count);
    }
    setThermalPanBufferPointer(getThermalPanBufferPointer() + 1);
  }
  //while(Wire.available()<1);
  //reading = Wire.read();
 
  //Serial.println();
  //delay(60000);
}

void outputThermalData(){
  for(int x = 0; x < THERMALTILTBUFFERSIZE; x++){
    for(int i = 0; i < THERMALPANBUFFERSIZE; i++){
      Serial.print(getThermalBuffer(x, i) / 10);
      Serial.print(" ");
    }
    Serial.println("");
  }
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

double getThermalBuffer(int i, int j){
  if(j >= THERMALPANBUFFERSIZE || j < 0){
    Serial.println("Thermal Buffer Pan Access Error");
    return 0; 
  }
  if(i >= THERMALPANBUFFERSIZE || i < 0){
    Serial.println("Thermal Buffer Tilt Access Error");
    return 0; 
  }
  return thermalBuffer[i][j]; 
}

void setThermalBuffer(double val, int i, int j){
  if(j > THERMALPANBUFFERSIZE || j < 0){
    Serial.println("Error setting thermal buffer pan data");
    return; 
  }
  if(i >= THERMALPANBUFFERSIZE || i < 0){
    Serial.println("Error setting thermal buffer tilt data");
    return 0; 
  }
  thermalBuffer[i][j] = val; 
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
