#include <stdlib.h>
float test = 78912.03456;
char buf[12];
String testString = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  convertCoord();
  for(int i = 0; i<testString.length();++i)
    selectNumber(testString[i]);

}
void selectNumber(char num){ //transmits GPS coordinates as audio
  if(num == '0')
    //startPlayback(zero, sizeof(zero));
    Serial.println(num);
  else if(num == '1')
    //startPlayback(one, sizeof(one));
    Serial.println(num);
  else if(num == '2')
    //startPlayback(two, sizeof(two));
    Serial.println(num);
  else if(num == '3')
    //startPlayback(three, sizeof(three));
    Serial.println(num);
  else if(num == '4')
//startPlayback(four, sizeof(four));
Serial.println(num);
  else if(num == '5')
   // startPlayback(five, sizeof(five));
   Serial.println(num);
  else if(num == '6')
   // startPlayback(six, sizeof(six));
   Serial.println(num);
  else if(num == '7')
   // startPlayback(seven, sizeof(seven));
   Serial.println(num);
  else if(num == '8')
   // startPlayback(eight, sizeof(eight));
   Serial.println(num);
  else if(num == '9')
   // startPlayback(nine, sizeof(nine));
   Serial.println(num);
  else if(num == '.')
  //  startPlayback(point, sizeof(point));
  Serial.println(num);
  else if(num == '-')
  //  startPlayback(neg, sizeof(neg)); 
  Serial.println(num);
  delay(1000);
  //stopPlayback();
}
void convertCoord(){ 
  dtostrf(test, 5, 5, buf);  //4 is mininum width, 6 is precision
  testString += buf;

}
