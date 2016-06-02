// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>


// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 

  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
void initiateAudio()
{
    if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);
}

void playfile(int filenum)
{
 if(filenum == 0)
  musicPlayer.playFullFile("zero.mp3");
 else if(filenum == 1)
  musicPlayer.playFullFile("one.mp3");
 else if(filenum == 2)
  musicPlayer.playFullFile("two.mp3");
 else if(filenum == 3)
  musicPlayer.playFullFile("three.mp3"); 
 else if(filenum == 4)
  musicPlayer.playFullFile("four.mp3"); 
 else if(filenum == 5)
  musicPlayer.playFullFile("five.mp3"); 
 else if(filenum == 6)
  musicPlayer.playFullFile("six.mp3"); 
 else if(filenum == 7)
  musicPlayer.playFullFile("seven.mp3"); 
 else if(filenum == 8)
  musicPlayer.playFullFile("eight.mp3"); 
 else if(filenum == 9)
  musicPlayer.playFullFile("nine.mp3"); 
 else if(filenum == 10)
  musicPlayer.playFullFile("dot.mp3"); 
 else if(filenum == 11)
  musicPlayer.playFullFile("neg.mp3"); 
 else if(filenum == 12)
  musicPlayer.playFullFile("lat.mp3"); 
 else if(filenum == 13)
  musicPlayer.playFullFile("long.mp3"); 
 else if(filenum == 14)
  musicPlayer.playFullFile("car.mp3");   
}
