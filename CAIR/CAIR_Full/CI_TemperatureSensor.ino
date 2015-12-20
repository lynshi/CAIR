//Measures ambient temperature

//On DHT11
//1 - VDD
//2 - DATA
//3 - NULL
//4 - GND

#include<dht11.h>

dht11 tempSensor;
#define TEMPSENSORPIN 8

int senseDelay = 1000;
double temperature;

//Actually useful functions
void measureTemperature(){
  int chk = tempSensor.read(TEMPSENSORPIN); //.read returns a value determining if operation was successful
  switch (chk)
  {
    case DHTLIB_OK: 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.println("Checksum error"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.println("Time out error"); 
		break;
    default: 
		Serial.println("Unknown error"); 
		break;
  }
  
  setTemperature(((tempSensor.temperature*9)/5) + 32); //converts stored temperature to Fahrenheit
}

//Mildly useful (for display purposes
void displayTemperature(){
  Serial.print("Temperature (°F): ");
  Serial.println((float)getTemperature(), 2);
}

void displayHumidity(){ //humidity doesn't matter to CAIR
  Serial.print("Humidity (%): ");
  Serial.println((float)getHumidity(), 2);
}

//Gets and Sets
double getTemperature(){ //returns temperature (Fahrenheit)
  return temperature; 
}

void setTemperature(double i){
  temperature = i; 
}

int getHumidity(){
  return tempSensor.humidity; 
}

void setSenseDelay(int i){
  senseDelay = i;
}

int getSenseDelay(){
  return senseDelay; 
}

//Testing
int testTempSensor() {
  measureTemperature();
  displayHumidity();
  displayTemperature();  
  return 0;
}
