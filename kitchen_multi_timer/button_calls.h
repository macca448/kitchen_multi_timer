void singleClick(void) {  
  if(clickMode == Menu){
    bool check = checkIfRunning(activeTimer, value);
    if(check)return;
    lastClickMode = value;
      switch (value){
        case Cancel:
          strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[Blank])));
          if(activeTimer == 1){
            timer1 = 0; t1Day = 0; t1Hour = 0; t1Min = 0; t1Sec = 0;
            t1Run = 0;
           lcd.setCursor(2,1);lcd.print(buffer);
          }else if(activeTimer == 2){
            timer2 = 0; t2Day = 0; t2Hour = 0; t2Min = 0; t2Sec = 0;
            t2Run = 0;
            lcd.setCursor(13,1);lcd.print(buffer);
          }else if(activeTimer == 3){
            timer3 = 0; t3Day = 0; t3Hour = 0; t3Min = 0; t3Sec = 0;
            t3Run = 0;
            lcd.setCursor(2,2);lcd.print(buffer);
          }else if(activeTimer == 4){
            timer4 = 0; t4Day = 0; t4Hour = 0; t4Min = 0; t4Sec = 0;
            t4Run = 0;
            lcd.setCursor(13,2);lcd.print(buffer);
          }else if(activeTimer == 5){
            timer5 = 0; t5Day = 0; t5Hour = 0; t5Min = 0; t5Sec = 0;
            t5Run = 0;
            lcd.setCursor(2,3);lcd.print(buffer);
          }else if(activeTimer == 6){
            timer6 = 0; t6Day = 0; t6Hour = 0; t6Min = 0; t6Sec = 0;
            t6Run = 0;
            lcd.setCursor(13,3);lcd.print(buffer);
          }
        break;

        case Start:
          if(activeTimer == 1){
            timer1 = configTimer(t1Day, t1Hour, t1Min, t1Sec);
            if(timer1 > 0 ){t1Run = 1; print_timer(activeTimer, timer1);}
          }else if(activeTimer == 2){            
            timer2 = configTimer(t2Day, t2Hour, t2Min, t2Sec);
            if(timer2 > 0){t2Run = 1; print_timer(activeTimer, timer2);}
          }else if(activeTimer == 3){            
            timer3 = configTimer(t3Day, t3Hour, t3Min, t3Sec);
            if(timer3 > 0){t3Run = 1; print_timer(activeTimer, timer3);}
          }else if(activeTimer == 4){            
            timer4 = configTimer(t4Day, t4Hour, t4Min, t4Sec);
            if(timer4 > 0){t4Run = 1; print_timer(activeTimer, timer4);}
          }else if(activeTimer == 5){            
            timer5 = configTimer(t5Day, t5Hour, t5Min, t5Sec);
            if(timer5 > 0){t5Run = 1; print_timer(activeTimer, timer5);}
          }else if(activeTimer == 6){            
            timer6 = configTimer(t6Day, t6Hour, t6Min, t6Sec);
            if(timer6 > 0){t6Run = 1; print_timer(activeTimer, timer6);}
          }
        break;

        case Seconds:
          clickMode = ChooseSecValue;
          lcd.setCursor(0,0);
          strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[ChooseSecValue])));
          lcd.print(buffer);
          value = 0;
        break;

        case Hours:
          clickMode = ChooseHourValue;
          lcd.setCursor(0,0);
          strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[ChooseHourValue])));
          lcd.print(buffer);
          value = 0;
        break;

        case Minutes:
          clickMode = ChooseMinValue;
          lcd.setCursor(0,0);
          strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[ChooseMinValue])));
          lcd.print(buffer);
          value = 0;
        break;

        case Days:
          clickMode = ChooseDayValue;
          lcd.setCursor(0,0);
          strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[ChooseDayValue])));
          lcd.print(buffer);
          value = 0;
        break;

        case Select:
          clickMode = ChooseTimerValue;
          lcd.setCursor(0,0);
          strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[ChooseTimerValue])));
          lcd.print(buffer);
          lcd.setCursor(13, 0);
          lcd.print(activeTimer);
        break;        
      }
      return;
  }else if(clickMode > Cancel && clickMode < Blank){
    clickMode = Menu;
    value = lastClickMode;
    char buf[3];
    sprintf(buf,"T:%i", activeTimer);
    lcd.setCursor(0, 0);
    strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[lastClickMode])));
    lcd.print(buffer);
    lcd.setCursor(17, 0);
    lcd.print(buf);
  }
} // singleClick

void doubleClick(void){  
  if(clickMode == TimeDisp){
    lcdOFF = 1;
    lcd.off();
  }
  if(clickMode == Menu){
    clickMode = TimeDisp;
  }
} // doubleClick

void longClick(void){
  digitalWrite(led, LOW);
  noTone(alarmPin);
  alarm = false;
} // longClick