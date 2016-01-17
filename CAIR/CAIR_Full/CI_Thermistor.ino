//measure ambient temperature

// Pin that the thermistor is connected to
#define PINTHERMISTOR A1
// Nominal temperature value for the thermistor
#define THERMISTORNOMINAL 1000
// Nominl temperature depicted on the datasheet
#define TEMPERATURENOMINAL 25
// Number of samples 
#define NUMS 5
// Beta value for our thermistor
#define BCOEFFICIENT 3500
// Value of the series resistor
#define SERIESRESISTOR 998

#define TEMPTHRESHOLD 60

int tempSenseDelay = 1000;
int reads[NUMS];
int i;
float temperature;
bool temperatureStatus; //0 below threshold, 1 above threshold

bool checkTemperatureStatus(){ //0 below threshold, 1 above threshold
  measureTemperature();
  displayTemperature();
  if(getTemperature() < TEMPTHRESHOLD){
    return 0; 
  }
  else{
    return 1; 
  }
}

void measureTemperature() {
  float avg;
  
  // for (i=0; i< NUMS; i++) {
  // reads[i] = analogRead(PINTHERMISTOR);
  // delay(10);
  // }
  
  // avg = 0;
  // for (i=0; i< NUMS; i++) {
  // avg += reads[i];
  // }
  // avg /= NUMS;
  
  // Convert the thermal stress value to resistance
  avg = analogRead(PINTHERMISTOR);
  avg = 1023 / avg - 1;
  avg = SERIESRESISTOR / avg;
  
  //Calculate temperature using the Beta Factor equation
  
  temperature = avg / THERMISTORNOMINAL;     // (R/Ro)
  temperature = log(temperature); // ln(R/Ro)
  temperature /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  temperature += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                 // Invert the value
  temperature -= 273.15; 
//  Serial.print("The sensor temperature is: ");
//  Serial.print(temperature);
//  Serial.println(" *C");                        // Convert it to Celsius
  temperature = (temperature*(9.0/5.0)+32);
//  Serial.print(temperature);
//  Serial.println(" *F");
  
  setTemperature(temperature);
}

void displayTemperature(){
  Serial.print("The temperature is currently: "); 
  Serial.print(getTemperature());
  Serial.println("*F");
}

float getTemperature(){
  return temperature; 
}

void setTemperature(float t){
  temperature = t; 
}

int getTempSenseDelay(){
  return tempSenseDelay; 
}

void setTempSenseDelay(int d){
  tempSenseDelay = d; 
}

bool testTempSensor(){
  measureTemperature();
  displayTemperature();
  return 0; 
}
