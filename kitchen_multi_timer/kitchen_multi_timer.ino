
#define PRINT true                          //only needed for debugging encoder so "false" on deploy

//Libraries
#include <Arduino.h>
#include <Wire.h>                           //One of controllers default library's
#include <OneButton.h>                      //Library Manager or https://github.com/mathertel/OneButton
#include <hd44780.h>                        //Library Manager or https://github.com/duinoWitchery/hd44780
#include <hd44780ioClass/hd44780_I2Cexp.h>  //LCD with i2c expander i/o class header
#include <RTClib.h>                         //Library Manager or https://github.com/adafruit/RTClib
#include <RotEnc.h>                         //Library Manager or https://github.com/kanitawa/RotEnc

//Constants
const byte  btnPinEnc = 10, clkPinEnc = 11, datPinEnc = 12; //Rotary Encoder Pins
const byte  alarmPin = 8, led = 13;                         //Buzzer and LED Pins
#include "char_strings.h"                                   //LCD Strings for Menu and Options DO NOT MOVE!

#define ONE_MIN   0x3C                                      //Seconds in a minute
#define ONE_HOUR  0xE10                                     //Seconds in an Hour
#define ONE_DAY   0x15180                                   //Seconds in a Day
#define TIMEOUT1  0x78                                      //2 minute inactive timeout to swap menu to date & time 
#define TIMEOUT2  0x708                                     //30 minute inactive timeout to turn lcd OFF                               

//Variables
char        buffer[21];                     //To hold PROGMEM char string for next "lcd.print(buffer)"
int8_t      clickMode = Menu, lastClickMode, activeTimer = 1, value = 0;
bool        alarm = 0, t1Run = 0, t2Run = 0, t3Run = 0, t4Run = 0, t5Run = 0, t6Run = 0, lcdOFF = 0;
uint8_t     t1Day = 0, t1Hour = 0, t1Min = 0, t1Sec = 0, t2Day = 0, t2Hour = 0, t2Min = 0, t2Sec = 0, lastMin,
            t3Day = 0, t3Hour = 0, t3Min = 0, t3Sec = 0, t4Day = 0, t4Hour = 0, t4Min = 0, t4Sec = 0, timeOutCount = 0,
            t5Day = 0, t5Hour = 0, t5Min = 0, t5Sec = 0, t6Day = 0, t6Hour = 0, t6Min = 0, t6Sec = 0, lastSec;   
int32_t     timer1 = 0, timer2 = 0, timer3 = 0, timer4 = 0, timer5 = 0, timer6 = 0;

void layout(void);
void singleClick(void);
void doubleClick(void);
void longClick(void);
void updateMainMenu(int8_t val);
void setValue(uint8_t val, int8_t tt);
void on_rotenc_rotated_ccw(void);
void on_rotenc_rotated_cw(void);
void updateTime(void);
bool checkIfRunning(int8_t tt, int8_t val);
int32_t configTimer(uint8_t dd, uint8_t hhh, uint8_t mmm, uint8_t sss);
void print_timer(uint8_t tt, uint32_t totalSec);
void setValue(uint8_t val, int8_t tt);
void updateMainMenu(int8_t val);
void timerEnd(uint8_t tt);
void updateTimers(void);

//Library Objects
OneButton button;                             //Encoders Button
hd44780_I2Cexp lcd;                           //LCD with I2C backpack
RTC_DS1307 rtc;                               //Real Time Clock Module
RotEnc re(clkPinEnc, datPinEnc);              //For Encoder Knob/Dial

//Sketch Tab organizing  using ".h" header extension. Line location can be important so don't change
#include "timer_calls.h"                      //Timer actions
#include "button_calls.h"                     //Button actions
#include "encoder_calls.h"                    //Encoder Knob/Dial actions

void setup() {
  if(PRINT == true){
    Serial.begin(115200);
  }
  
  pinMode(led, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  
  Wire.begin();
  int status = lcd.begin(20, 4);
	if(status){                                       // non zero status means it was unsuccesful
		                                                // hd44780 has a fatalError() routine that blinks an led if possible
		                                                // begin() failed so blink error code using the onboard LED if possible
		hd44780::fatalError(status);                    // does not return
	}
  
  if (! rtc.begin()) {
    if(PRINT == true){
      Serial.println("Couldn't find RTC");
      Serial.flush();
    }
    abort();
  }

  button.setup(btnPinEnc, INPUT_PULLUP, true);      // button pin, SW Pullup, ACTIVE LOW
  button.attachLongPressStart(longClick);           // attach long click event
  button.attachDoubleClick(doubleClick);            // attach double click event
  button.attachClick(singleClick);                  // attach button single momentary press
  re.attachCallback_RotatedInCCW(on_rotenc_rotated_ccw);
  re.attachCallback_RotatedInCW(on_rotenc_rotated_cw);

   DateTime time = rtc.now();

  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  char buf[3];
  sprintf(buf,"T:%i",activeTimer);
  strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[Select])));
  lcd.print(buffer);
  lcd.setCursor(17,0);
  lcd.print(buf);
  lastSec = time.second();
  lastMin = time.minute();
  layout();
}

void loop() {
  
  DateTime time = rtc.now();
  
  re.poll();
  button.tick();
  
  if(lastSec != time.second()){    
    lastSec = time.second();
    timeOutCount++;
    updateTimers();
      if(timeOutCount >= TIMEOUT1 && clickMode != TimeDisp){
        clickMode = TimeDisp;
      }
      if(timeOutCount >= TIMEOUT2 && clickMode == TimeDisp){
        lcd.off();
        lcdOFF = 1;
      }
  } 
}
