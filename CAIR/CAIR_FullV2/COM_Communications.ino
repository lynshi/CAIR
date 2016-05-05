//Consolidates functions for calling

#include <Adafruit_FONA.h>
#include <stdlib.h>

#define FONA_RST           22

HardwareSerial *fonaSerial = &Serial1;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
char number[30] = /*{'9','1','7','3','1','8','6','2','5','0'};*/{'7','3','2','3','1','8','5','3','9','6'};
char latbuff[12];
char longbuff[12];
 
#define COORDSIZE 5
float latitude, longitude, speed_kph, heading, speed_mph, altitude;
//String latString = "";
//String longString = "";

void initiateCOM(){
  delay(100);  
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    return;
  }
  Serial.println(F("FONA is OK"));
  setupGPS();
}

//HERE IS THE GPS PART
void getCoord(){
  boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);
  convertCoord();
}

void setupGPS(){
  fona.enableGPS(true); 
}

void setLong(float x ){
  longitude = x;  
}

void setLat(float x ){
  latitude = x;  
}

void getLongit(){
  for(int i = 0; longbuff[i]!='\0';i++)
    Serial.print(longbuff[i]);
  Serial.println();
} 

void getLat(){
  for(int i = 0; latbuff[i]!='\0';i++)
    Serial.print(latbuff[i]);
  Serial.println();
} 

void convertCoord(){ 
  dtostrf(latitude, 5, 5, latbuff);  //4 is mininum width, 6 is precision
  
  dtostrf(longitude, 5, 5, longbuff);  //4 is mininum width, 6 is precision
}

void printCoord(){
  Serial.println("GPS Coordinates");
  Serial.print("Latitude: ");
  getLat();
  Serial.print("Longitude: ");
  getLongit();
}

////HERE IS THE GSM PART

void contactEmerg(){ //contacts authorities
  Serial.print("GPS Status: ");
  Serial.println(fona.GPSstatus());
  placeCall();
  //"CHILD IN CAR"

  delay(1750);

  delay(1000);

  
  //"LATITUDE"

  delay(1500);

  for(int i = 0; latbuff[i]!='\0'; i++){
    selectNumber(latbuff[i]);
  }
  
  //"LONGITUDE"

  delay(1500);
 
  for(int i = 0; longbuff[i]!='\0'; i++){
    selectNumber(longbuff[i]);
  }
  delay(5000);
  fona.hangUp();
}

void placeCall(){ //places the call
  if (!fona.callPhone(number)) {
    Serial.println(F("Failed"));
  } 
  else {
    Serial.println(F("Sent!")); 
  }
  delay(1000);
  while(fona.getCallStatus() != 4)
  {
    //Serial.print(F("."));
    delay(500);
  }
  delay(20000);
}

void selectNumber(char num){ //transmits GPS coordinates as audio
  if(num == '0')
    
  if(num == '1')

  if(num == '2')

  if(num == '3')

  if(num == '4')

  if(num == '5')
 
  if(num == '6')
   
  if(num == '7')

  if(num == '8')
 
  else if(num == '9')

  else if(num == '.')

  else if(num == '-')

  delay(1000);

}
