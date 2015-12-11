//On DHT11
//1 - VDD
//2 - DATA
//3 - NULL
//4 - GND

#include<dht11.h>

dht11 tempSensor;
#define TEMPSENSORPIN 8

int senseDelay = 3000;
int temperature;

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
}

//Mildly useful (for display purposes
void displayTemperature(){
  Serial.print("Temperature (°C): ");
  Serial.println((float)getTemperature(), 2);
}

void displayHumidity(){ //humidity doesn't matter to CAIR
  Serial.print("Humidity (%): ");
  Serial.println((float)getHumidity(), 2);
}

//Gets and Sets
int getTempSensorPin(){
  return TEMPSENSORPIN; 
}

int getTemperature(){
  return tempSensor.temperature; 
}

int getHumidity(){
  return tempSensor.humidity; 
}

//Testing
int testTempSensor() {
  measureTemperature();
  displayHumidity();
  displayTemperature();  
  return 0;
}
