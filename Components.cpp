#include "Components.h"
#include "arduino.h"
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <SD.h>
#include <SPI.h>

File logfile;
//File myFile;
#include <SoftwareSerial.h>
float usartArray [100];
int usartIndex = 0;

SoftwareSerial mySerial(19, 18); // RX, TX
unsigned long presentMillis = 0;
const long intervalNow = 1000;
LiquidCrystal lcd(40, 38, 31, 29, 36, 34);
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};


Components::Components(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}


void Components::yellowLed() {
 
  digitalWrite(_pin, HIGH);   // turn the yellow LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(_pin, LOW);    // turn the yellow LED off by making the voltage LOW
  delay(1000);
  }
  // wait for a second
void Components::greenLed()
  {
  digitalWrite(_pin, HIGH);   // turn the  green LED on (HIGH is the voltage level)
  
  }
  // wait for a second
  void Components::redLed()
  {
  digitalWrite(_pin, HIGH);   // turn red the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(_pin, LOW);    // turn the red LED off by making the voltage LOW
  delay(1000);              // wait for a second
  }
  
void Components::buzzer() // turns on buzzer for 2 seconds
{
	tone(_pin, 4000, 2000);
}
void Components::motorOne() //sets first motor high and low
{
digitalWrite(_pin, HIGH);
delay(10000);
digitalWrite(_pin, LOW);
delay(1000);
}
void Components::motorTwo()  // sets second motor high and low
{
digitalWrite(_pin, HIGH);
delay(10000);
digitalWrite(_pin, LOW);
delay(1000);
}
void Components::motorThree()  // sets third motor high and low
{
digitalWrite(_pin, HIGH);
delay(10000);
digitalWrite(_pin, LOW);
delay(1000);
}
void lcdGreen() //Displays message to the LCD for the Green state
{
	// set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.leftToRight();
  lcd.print("Drive safely");
  lcd.setCursor(0, 0);
}
void lcdRed() //Displays message to the LCD for the Red state.
{
	// set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Take a 30 minutes!");
  lcd.setCursor(5, 1);
  lcd.print(" break!");
  
}
void lcdYellow() // displays message to LCD for the yellow state
{
	// set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("You need to be alert");
  rtcClock();
  delay(5000);
}

void setupRtcClock(){  //sets up RTC
	#ifndef ESP8266
  while (!Serial); 
#endif
lcd.begin(20, 4);
lcd.setCursor(0, 2);
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning())
 {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    
  }
 
}

void rtcClock(){  // prints time to the LCD
	 DateTime now = rtc.now();
	 
	  if (! rtc.isrunning())
 {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    
  }
	
    lcd.begin(20, 4);     // intializing the LCD module
	 lcd.setCursor(4, 2);    //sets cursor to the 3 row and 4th column.
	lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
   
	
    lcd.setCursor(2, 3);  // setting the cursor to row 4 and column 2
    
    lcd.print(now.day(), DEC);
	lcd.print('/');
	lcd.print(now.month(), DEC);
    lcd.print('/');
	lcd.print(now.year(), DEC);
    
    
    lcd.print(" (");
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(") ");
    
    delay(1000);
}
// call back for file timestamps
 void dateTime(uint16_t* date, uint16_t* time) {
 DateTime now = rtc.now();

 // return date using FAT_DATE macro to format fields
 *date = FAT_DATE(now.year(), now.month(), now.day());

 // return time using FAT_TIME macro to format fields
 *time = FAT_TIME(now.hour(), now.minute(), now.second());
} 
void stringTime () // converts time read from Real time clock to string
{
	   presentMillis = millis();
	   

	DateTime now = rtc.now();
	String stringOne = String(now.hour(), DEC);
    String stringTwo = String(now.minute(), DEC);

    String stringThree = String(now.second(), DEC);

     String stringFour =  String(now.day(), DEC);
     String stringFive = String(now.month(), DEC);
     String stringSix = String(now.year(), DEC);
     String stringSeven = String(daysOfTheWeek[now.dayOfTheWeek()]);

     String timeConct = stringOne + ":" + stringTwo + ":" + stringThree;
     String dateConct = stringFour + "/" + stringFive + "/" + stringSix ;
	 Serial.println(timeConct);
     Serial.println(stringSeven);
     Serial.println(dateConct);  
	 
	 
	 const int chipSelect = 53;

File logfile;
File logfiletxt;
File logfileName;

//Serial.print("Initializing SD card...");
  
  pinMode(53, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.print("Card failed, or not present");
  }
  Serial.println("card initialized.");
 
 // set date time callback function
 SdFile::dateTimeCallback(dateTime);

  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }

  if (! logfile) {
    Serial.print("couldnt create file");
  }
  
  Serial.print("Logging to: ");
  Serial.println(filename);
  logfile.println("Time,Day,Date,Warning,Break interval");
   
	  
  logfile.print(timeConct);
  logfile.print(", "); 
  logfile.print(stringSeven);
  logfile.print(", "); 
  logfile.print (dateConct);

	  logfile.print(", "); 
      logfile.println ("No");
	  logfile.print(", "); 
      logfile.println ("N/A");
	  if (SD.exists("datalog.txt"))
	  {
		  SD.remove("datalog.txt");
		  
	  }
	  
  logfiletxt = SD.open("datalog.txt", FILE_WRITE);
  logfiletxt.print(timeConct);
  logfiletxt.print(", "); 
  logfiletxt.print(stringSeven);
  logfiletxt.print(", "); 
  logfiletxt.print (dateConct);
  logfiletxt.print (filename);
  logfile.flush();
  logfiletxt.flush();
  
	 logfileName = SD.open("lognow.txt", FILE_WRITE);
    logfileName.print(filename);
}
int usartLoop( int returnValue){  //receive values from FPGA board, stores them in an array
	const long interval = 120000;
  unsigned long currentMillis = millis();
// set the data rate for the SoftwareSerial port
  int x;
  mySerial.begin(115200);
  mySerial.println("Hello, world?");
  float deltaAvg = 0;
  float thetaAvg = 0;
  float alphaAvg = 0;
  float betaAvg = 0;
  float betaOne = 0;
  float betaTwo = 0;

  while (mySerial.available()) {
   // Serial.write(mySerial.read());
       for (int j = 0; j<31; ++j) 
  {
    usartArray[usartIndex] = mySerial.read(); // Store it
    usartIndex++; // Increment where to write next
   
  }
    
   //delay(60000);
  }
  float oneHertz = usartArray[0];   //entries for delta waves
   float twoHertz = usartArray[1];
   float threeHertz = usartArray[2];
   float fourHertz = usartArray[3];
   
   float fiveHertz = usartArray[4];  //entries for theta waves
   float sixHertz = usartArray[5];
   float sevenHertz = usartArray[6];
   float eightHertz = usartArray[7];
   
   float nineHertz = usartArray[8];    //entries for alpha waves
   float tenHertz = usartArray[9];
   float elevenHertz = usartArray[10];
   float twelveHertz = usartArray[11];
   float thirteenHertz = usartArray[12];
   
   float fourteenHertz = usartArray[13];    // entries for beta waves
   float fifteenHertz = usartArray[14];
   float sixteenHertz = usartArray[15];
   float seventeenHertz = usartArray[16];
   float eighteenHertz = usartArray[17];
   float nineteenHertz = usartArray[18];
   float twentyHertz = usartArray[19];

   float t_oneHertz = usartArray[20];
   float t_twoHertz = usartArray[21];
   float t_threeHertz = usartArray[22];
   float t_fourHertz = usartArray[23];
   float t_fiveHertz = usartArray[24];

   float t_sixHertz = usartArray[25];
   float t_sevenHertz = usartArray[26];
   float t_eightHertz = usartArray[27];
   float t_nineHertz = usartArray[28];
   float thirtyHertz = usartArray[29];

    //deltaAvg = (oneHertz + twoHertz + threeHertz + fourHertz)/4;
    //thetaAvg = ( fiveHertz + sixHertz + sevenHertz + eightHertz)/4; 
    alphaAvg = (nineHertz + tenHertz + elevenHertz + twelveHertz + thirteenHertz)/5;
    //betaOne = (fourteenHertz + fifteenHertz + sixteenHertz + seventeenHertz + eighteenHertz + nineteenHertz + twentyHertz + t_oneHertz);

    int betaMax;
      betaMax = max(fourteenHertz, fifteenHertz);
      betaMax = (betaMax, sixteenHertz);
      betaMax = (betaMax, seventeenHertz );
      betaMax = (betaMax, eighteenHertz );
      betaMax = (betaMax, nineteenHertz );
      betaMax = (betaMax, twentyHertz  );
      betaMax = (betaMax, t_oneHertz );

      betaMax = (betaMax, t_twoHertz );
      betaMax = (betaMax, t_threeHertz );
      betaMax = (betaMax, t_fourHertz );
      betaMax = (betaMax, t_fiveHertz );
      betaMax = (betaMax, t_sixHertz  );
      betaMax = (betaMax, t_sevenHertz );
      
      betaMax = (betaMax, t_eightHertz );
      betaMax = (betaMax, t_nineHertz );
      betaMax = (betaMax, thirtyHertz );

      int alphaMax;

      alphaMax = max(nineHertz, tenHertz);
      alphaMax = (betaMax, elevenHertz);
      alphaMax = (betaMax, twelveHertz );
      alphaMax = (betaMax, thirteenHertz );


      if (( alphaMax/betaMax) < 1)
      {
        x = 010;
        Serial.print(x);
      }

        if (( alphaMax/betaMax) > 1)
        {
          x= 001;
          Serial.print(x);
        }
        

   return x;
}





void readTextFile() { // Reads value from datalog.txt to get the time the driver was received a warning to take a break
                      //calculates the time the driver spent on his break. Then opens the logfile to enter the breaktime
 setupRtcClock();
 int inputString [100]; //array declaration
int stringIndex = 0; // String stringIndexing in
 
   
  Serial.begin(9600);
  const int chipSelect = 53;
  File myFile;
  File addValues;
Serial.print("Initializing SD card...");
pinMode(53, OUTPUT);

   if (!SD.begin(chipSelect)) {
    Serial.print("Card failed, or not present");
  }
  Serial.println("card initialized.");
  
 
  
 myFile = SD.open("datalog.txt", FILE_READ); // open the txt file to extract values
  if (!myFile) {
    Serial.println("Can't open file");
    return;
  }

  while (myFile.available()) {
      for (int j = 0; j<9; ++j) 
  {
    inputString[stringIndex] = myFile.parseInt(); //prints only the integer values from the txt file
    stringIndex++; // Increment where to write next
   
  }
    
         
  }
  myFile.close(); 
  for (int i = 0; i < 7; i = i + 1) { //for testing: prints values to serial monitor
  Serial.println(inputString[i]);
}
int hourPrev = inputString[0]; //get values from array
int minutesPrev = inputString[1];
int datePrev = inputString[3];
int monthPrev = inputString[4];
int yearPrev =inputString[5];
RTC_DS1307 rtc;//for testing

//Getting current time
DateTime now = rtc.now();

int hourNow = (now.hour(), DEC);;  
int minutesNow = (now.minute(), DEC);
int dateNow = (now.day(), DEC);
int monthNow = (now.month(), DEC);
int yearNow =(now.year(), DEC);

int appendName = inputString[6];
String holdFilename ;
if (appendName <= 9)
{
	holdFilename = "0" + String(appendName);
}	
 else if (appendName > 9)
{
 holdFilename = String(appendName);
}
 
String filesearchString = ("LOGGER" + holdFilename + ".CSV");  //concatenate value read off the txt file to other strings to create a complete file name
char fileSearch[100];  //declare character array
filesearchString.toCharArray(fileSearch, 100); //converts string to character array
Serial.print(fileSearch);// for testing

//comparison to see if the present time and the previous time is within a range to warrant a comparison 
if (((datePrev == dateNow) && (monthPrev == monthNow) && (yearPrev == yearNow))||((dateNow - datePrev == 1)&& (yearPrev == yearNow)) ||((dateNow ==1)&&(monthNow - monthPrev ==1) && (yearNow == yearPrev)))
{
  if (hourNow == 0) // sets the hour value to 24 if the time is at midnight
  {
    hourNow = 24;
  }
  if (hourPrev > hourNow)
  {
	  hourNow = hourNow + 24;
  }
  int totalTimeMin = ((hourNow * 60) + minutesNow)- ((hourPrev * 60) + minutesPrev); //math to get the time difference
  
  addValues = SD.open(fileSearch, FILE_WRITE); //open the already existing file to append new values
  if (!addValues) {
    Serial.println("Can't open file");
    return;
  }
   addValues.print(totalTimeMin); //Print totalTimeMin as breakTime
   addValues.flush();

}

}
int  laststate( int y) {
	int x;
 if (SD.exists("laststate.txt"))
   {

    x = 43;
   }
   else
   {
    x= 44;
   }
   return x;
   }
   
void createlastState() {  //creates a txt file if the last state before the car was turned off was red.
  Serial.begin(9600);
  const int chipSelect = 53;
  Serial.print("Initializing SD card...");
   pinMode(53, OUTPUT);

   if (!SD.begin(chipSelect)) {
    Serial.print("Card failed, or not present");
  }
  Serial.println("card initialized.");
  File lastState; // creates file

  
   if (! SD.exists("lognow.txt"))
   {
  lastState = SD.open("lognow.txt", FILE_WRITE); // open the txt file to write value
  lastState.print("redstate");
  lastState.flush();
   } 
}

void deletelastState() { //delete txt file that keeps track of the last state beore the car was turmed off.
  
   if ( SD.exists("lognow.txt"))
   {
  SD.remove("lognow.txt");
   } 
}
void logAppend() {   // Records that driver ignored warnings after 5 minutes wait
  Serial.begin(9600);
  const int chipSelect = 53;
  File lastFile;
  File addFile;
  int inputString [10];
  int stringIndex = 0; // String stringIndexing in
Serial.print("Initializing SD card...");
pinMode(53, OUTPUT);

   if (!SD.begin(chipSelect)) {
    Serial.print("Card failed, or not present");
  }
  Serial.println("card initialized.");

  lastFile = SD.open("lognow.txt", FILE_READ); // open the txt file to extract values
  if (!lastFile) {
    Serial.println("Can't open file");
    return;
  }

  if (lastFile.available()) {
      
    inputString[stringIndex] = lastFile.parseInt(); //prints only the integer values from the txt file
    //stringIndex++; // Increment where to write next
   
  }
   int fileNumber = inputString[0];

    String holdFilename;
if (fileNumber <= 9)
{
  holdFilename = "0" + String(fileNumber);
} 
else if (fileNumber > 9)
{
 holdFilename = String(fileNumber);
}

String filesearchString = ("LOGGER" + holdFilename + ".CSV");  //concatenate value read off the txt file to other strings to create a complete file name
char fileSearch[100];  //declare character array
filesearchString.toCharArray(fileSearch, 100); //converts string to character array
Serial.print(fileSearch);// for testing
  
  
  
if (SD.exists(fileSearch))
	  {
		  SD.remove(fileSearch);
		  
	  }
	  
addFile = SD.open(fileSearch, FILE_WRITE); //open the already existing file to append new values
  
  if (!addFile) {
    Serial.println("Can't open file");
    return;
  }
  
  DateTime now = rtc.now();
	String stringOne = String(now.hour(), DEC);
    String stringTwo = String(now.minute(), DEC);

    String stringThree = String(now.second(), DEC);

     String stringFour =  String(now.day(), DEC);
     String stringFive = String(now.month(), DEC);
     String stringSix = String(now.year(), DEC);
     String stringSeven = String(daysOfTheWeek[now.dayOfTheWeek()]);

     String timeConct = stringOne + ":" + stringTwo + ":" + stringThree;
     String dateConct = stringFour + "/" + stringFive + "/" + stringSix ;
	 Serial.println(timeConct);
     Serial.println(stringSeven);
     Serial.println(dateConct);  
	 
  addFile.println("Time,Day,Date,Warning,Break interval");
  
  addFile.print(timeConct); 
  addFile.print(","); 
  addFile.print(stringSeven);
  addFile.print(","); 
  addFile.print(dateConct);  
  addFile.print(","); 
  addFile.print("NO"); //Print totalTimeMin as breakTime
  addFile.print ("N/A");
   addFile.flush();
   addFile.close();


  }
  

