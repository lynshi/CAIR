//Uses Omron Thermal Sensor to detect heat and humans

#include <Wire.h>

//1 GND Ground
//2 VCC Power source (5V +/-10%)
//3 SDA I2C(5V) Data line
//4 SCL I2C(5V) Clock line

#define THERMALPANBUFFERSIZE 68
#define THERMALTILTBUFFERSIZE 3

int reading;
int thermalReadDelay = 500;
int count;
int thermalPanBufferPointer;
int thermalTiltBufferPointer;

double thermalPanBuffer[THERMALTILTBUFFERSIZE][THERMALPANBUFFERSIZE];
 
void thermalSensorSetup(){
  Wire.begin(); 
  thermalPanBufferPointer = 0;
  thermalTiltBufferPointer = 0;
  count = 0;
  reading = 0;
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
 
  count=0;
 
  while(count<34){
  //Serial.print("Count NOT AVAILABLE: "); 
  //Serial.println(count);
  if(2 <= Wire.available())    // if two bytes were received
    {
   
      reading = Wire.read();  // receive high byte (overwrites previous reading)
   
      reading += Wire.read()<<8;
      
      setThermalBuffer(reading, (count/2) + (getThermalPanBufferPointer() * 17));
   
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

double getThermalBuffer(int i){
  if(i > THERMALPANBUFFERSIZE || i < 0){
    Serial.println("Thermal Buffer Access Error");
    return 0; 
  }
  return thermalPanBuffer[getThermalTiltBufferPointer()][i]; 
}

void setThermalBuffer(double val, int i){
  if(i > THERMALPANBUFFERSIZE || i < 0){
    Serial.println("Thermal Buffer Setting Error");
    return; 
  }
  thermalPanBuffer[getThermalTiltBufferPointer()][i] = val; 
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
