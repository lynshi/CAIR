void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  for(int i = 0; i < 192; i++){
    if(i == 13 || i == 14 || i == 15 || i == 29 || i == 30 || i == 31 || i == 45 || i == 46 || i == 47){
      Serial.print(random(270,300));
    }
    else{
      Serial.print(random(150,200)); 
    }
    Serial.print(" ");
  }
  Serial.print(".");
  //delay(60000);
}
