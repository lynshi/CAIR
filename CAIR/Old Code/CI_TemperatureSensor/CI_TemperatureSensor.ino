//Measures ambient temperature

//On DHT11
//1 - VDD
//2 - DATA
//3 - NULL
//4 - GND

#include<dht11.h>

dht11 tempSensor;
#define TEMPSENSORPIN 8
#define TEMPADJUST 0 
#define TEMPTHRESHOLD 60

int tempSenseDelay = 2000;
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
  
  //setTemperature(tempSensor.temperature); //Celsius
  setTemperature(((tempSensor.temperature*9)/5) + 32 - TEMPADJUST); //converts stored temperature to Fahrenheit and adjusts for internal error
}

int checkTemperature(){ //return 0 below threshold, 1 >= threshold
  measureTemperature();
  displayTemperature(); //FOR DEMONSTRATION ONLY NOT IN FINAL PRODUCT----------------------------------------------------------------------------------------------------
  delay(1000);
  if(getTemperature() < TEMPTHRESHOLD){
    return 0; 
  }
  else{
    return 1; 
  }
}

//Mildly useful (for display purposes
void displayTemperature(){
  Serial.print("Temperature (F): ");
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

void setTempSenseDelay(int i){
  tempSenseDelay = i;
}

int getTempSenseDelay(){
  return tempSenseDelay; 
}

//Testing
int testTempSensor() {
  delay(getTempSenseDelay());
  measureTemperature();
  //displayHumidity();
  displayTemperature();  
  return 0;
}
