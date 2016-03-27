#include <stdlib.h>

void setup() {
  int i;
  float val;
  char buff[12];
  String valueString = "";
  Serial.begin(115200);
  val = 74.54432;
    dtostrf(val, 5, 5, buff);  //4 is mininum width, 6 is precision
    //Serial.print("val: ");
    //Serial.println(val);
    valueString += buff;
  Serial.println(valueString);
}

void loop() {
}
