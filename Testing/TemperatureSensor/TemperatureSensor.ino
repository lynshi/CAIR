// //On DHT11
// //1 - VDD
// //2 - DATA
// //3 - NULL
// //4 - GND

// #include<dht11.h>

// dht11 DHT11A;
// #define DHT11APIN 8

// int senseDelay = 3000;

// void setup() {
//   Serial.begin(9600);
//   Serial.println("DHT11 TEST PROGRAM");
//   Serial.println();
//   delay(1000);
// }

// void loop() {
//   int chk = DHT11A.read(DHT11APIN);
//   switch (chk)
//   {
//     case DHTLIB_OK: 
// 		Serial.println("OK"); 
// 		break;
//     case DHTLIB_ERROR_CHECKSUM: 
// 		Serial.println("Checksum error"); 
// 		break;
//     case DHTLIB_ERROR_TIMEOUT: 
// 		Serial.println("Time out error"); 
// 		break;
//     default: 
// 		Serial.println("Unknown error"); 
// 		break;
//   }
  
//   delay(500);
  
//   Serial.print("Humidity (%): ");
//   Serial.println((float)DHT11A.humidity, 2);

//   Serial.print("Temperature (°C): ");
//   Serial.println((float)DHT11A.temperature, 2);
  
//   delay(2500);
// }
