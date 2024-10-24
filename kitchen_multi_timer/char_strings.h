
enum mainList {Select, Start, Minutes, Hours, Days, Seconds, Cancel, 
               ChooseMinValue, ChooseHourValue, ChooseDayValue, ChooseSecValue, ChooseTimerValue, 
               Blank, EndTimer1, EndTimer2, EndTimer3, EndTimer4, EndTimer5, EndTimer6, Menu, TimeDisp};

const char ch00[] PROGMEM = "SELECT TIMER      ",
           ch01[] PROGMEM = "START TIMER       ",
           ch02[] PROGMEM = "SET MINUTES       ",
           ch03[] PROGMEM = "SET HOURS         ",
           ch04[] PROGMEM = "SET DAYS          ",
           ch05[] PROGMEM = "SET SECONDS       ",          
           ch06[] PROGMEM = "CANCEL TIMER      ",
           ch07[] PROGMEM = "SELECT MIN   ",     //set active timer at "lcd.setCursor(14,0);"
           ch08[] PROGMEM = "SELECT HOUR  ",
           ch09[] PROGMEM = "SELECT DAYS  ",
           ch10[] PROGMEM = "SELECT SEC   ",
           ch11[] PROGMEM = "NEW TIMER CT:",
           ch12[] PROGMEM = "  00:00",
           ch13[] PROGMEM = " END T1",
           ch14[] PROGMEM = " END T2",
           ch15[] PROGMEM = " END T3",
           ch16[] PROGMEM = " END T4",
           ch17[] PROGMEM = " END T5",
           ch18[] PROGMEM = " END T6";

const char *const mainMenu[] PROGMEM = 
  {ch00, ch01, ch02, ch03, ch04, ch05, ch06, ch07, ch08, ch09, ch10, ch11, ch12, ch13, ch14, ch15, ch16, ch17, ch18};

