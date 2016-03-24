#include <Adafruit_FONA.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  double orig = 9876.5432;  
  Serial.print("First orig is: ");
  Serial.println(orig,6);
  orig /= 1000.0;
  int store;
  
  for(int i = 0; i < 8; i++){
    store = orig; 
    Serial.print("Store = ");
    Serial.println(store);
    orig -= store;
    orig *= 10.0;
    Serial.print("Orig = ");
    Serial.println(orig,6);
  }
  delay(60000);
}
