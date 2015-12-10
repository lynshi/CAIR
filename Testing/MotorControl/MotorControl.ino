#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 30;    // variable to store the servo position 
int choice = 0;
int time = 100;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{   
  if(choice == 0){
    for(pos = 30; pos < 150; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(time);                       // waits 15ms for the servo to reach the position 
    } 
    for(pos = 160; pos>=30; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(time);                       // waits 15ms for the servo to reach the position 
    }   
  }
  
  else if(choice == 1){
    for(pos = 0; pos < 1800; pos += 2)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.writeMicroseconds(map(pos,0,1800,525,2260));              // tell servo to go to position in variable 'pos' 
      delay(time);                       // waits 15ms for the servo to reach the position 
    } 
    for(pos = 1800; pos>=0; pos-=2)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.writeMicroseconds(map(pos,0,1800,525,2260));              // tell servo to go to position in variable 'pos' 
      delay(time);                       // waits 15ms for the servo to reach the position 
    } 
  }
}
