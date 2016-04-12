#include <Components.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <SD.h>




 
word w = 100;
Components yellowLedPin(23);
Components redLedPin(39);
Components greenLedPin(43);
Components buzzerPin(37);
Components motorPinOne(45);
//Components motorPinTwo(42);
//Components motorPinThree(41);
const long interval = 108000;
const long countOne = 10000;
const long timeLog = 180000;
int lastState = 0;
int carRunning = 1;

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

void setup() {
  // put your setup code here, to run once:
 setupRtcClock();
 Serial.begin(9600);
 
 

}


 
void loop() {
 
 //lastState = laststate(1);
// lastState = 43;
//Serial.print(lastState); // for testing
//   if ((carRunning = 0) && (lastState== 43)) //check to see if car was turned off and if the last state was red
//    {
//    readTextFile(); //call function to log the amount of break that was taken 
//    
//  }

  w = 001;
  //int w = usartLoop(1);

  if (w==100 ) //conditional statement for yellow state
  {
    unsigned long currentMillis = millis();
    deletelastState();  //delete text file to keep track of the last state before the car was turned off
    if (currentMillis  <= interval)
    {
       
  yellowLedPin.yellowLed(); //activate yellow led
  buzzerPin.buzzer();      //activate buzzer
  lcdYellow();             //print message to LCD
  rtcClock();              //print time to LCD
  carRunning = 1;        //set car is running state to 1
    }
  }
    else if (w== 010)   //conditional statement for green state
  {
   greenLedPin.greenLed();   //activate green LED
  deletelastState();  //delete text file to keep track of the last state before the car was turned off
   lcdGreen();              //display message on LCD
   //setupRtcClock();
   rtcClock();             //print time to LCD
   carRunning = 1;         //set car is running state to 1
   
  }
   else if (w == 001) //conditional statement for red state
  {
     createlastState();       //create text file to keep track of last state before the car was turned off
    
    currentMillis = millis();
     if (currentMillis  <= interval) //make alarm go off for one minute
    {
  redLedPin.redLed();
 //unsigned long stringMillis = millis();
  if (currentMillis <= countOne){
  stringTime (); // log time of warning
  
  }
 // returnValues();
  lcdRed();   //write to LCD
  rtcClock();  // print time to LCD
  buzzerPin.buzzer();
   motorPinOne.motorOne();
  //motorPinTwo.motorTwo();
// motorPinThree.motorThree();
 carRunning = 1;
    } 

     if (currentMillis >= timeLog)
     {
      logAppend ();
     }
  }
  else 
  {
    greenLedPin.greenLed();
    rtcClock(); //print time to LCD
  }
  
  
 
}


