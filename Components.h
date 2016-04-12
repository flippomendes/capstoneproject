#ifndef Components_h
#define Components_h
#include "Arduino.h"
#include <SD.h>
#include <SPI.h>


class Components
{
  public:
Components(int yellow);
void yellowLed();
void redLed();
void greenLed();
void buzzer();
void motorOne();
void motorTwo();
void motorThree();
private:
int _pin;

};

void lcdGreen();
void lcdYellow();
void lcdRed();
void usartSetup();
void usartLoop();
void setupRtcClock();
void rtcClock();
void printTime();
void rtcLogTime();
void stringTime ();
void dateTime(uint16_t* date, uint16_t* time);
void readTextFile();
int laststate( int y);
void createlastState() ;
void deletelastState();
void logAppend();
#endif