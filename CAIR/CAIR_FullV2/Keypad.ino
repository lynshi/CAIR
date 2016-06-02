#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {45, 43, 41, 39}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {37, 35, 33}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char readKeypad(){
  char key;
  while(1){ //keep running until a key is pressed
    key = keypad.getKey();
    if (key != NO_KEY){
      Serial.println(key);
      return key;
    }
  }
}

void getPhoneNumber(){ //allows the user to enter his/her phone number
  int i = 0;
  char c;
  
  Serial.println("Please enter your phone number on the keypad. If you would like to restart entering your number, please press the * key.");
  
  while(1){ //Must press # key to exit
    c = readKeypad();
    if(c == '*'){
      i = 0;
      continue; 
    }
    if(c == '#' && i >= 10){
      return; 
    }
    if(i < 10){
      setNumber(c, i);
      i++;
    }  
  }
}
