
void layout(void){
  strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[Blank])));
  lcd.setCursor(0,1); lcd.print("1:"); lcd.print(buffer);
  lcd.setCursor(11,1); lcd.print("2:"); lcd.print(buffer);
  lcd.setCursor(0,2); lcd.print("3:"); lcd.print(buffer);
  lcd.setCursor(11,2); lcd.print("4:"); lcd.print(buffer);
  lcd.setCursor(0,3); lcd.print("5:"); lcd.print(buffer);
  lcd.setCursor(11,3); lcd.print("6:"); lcd.print(buffer);
  return;
}

void updateTime(void){
  DateTime time = rtc.now();
  lcd.setCursor(0,0);
  //char buff_tt[] = "DDD MMM DD  hh:mm:ss";
  //lcd.print(time.toString(buff_tt));
  char buf[21];
  sprintf(buf,"DDD DD MMM  %02u:%02u:%02u", time.hour(), time.minute(), time.second());
  lcd.print(time.toString(buf));  
  return;
}

int32_t configTimer(uint8_t dd, uint8_t hhh, uint8_t mmm, uint8_t sss){
  int32_t x;
          x  = sss;
          x += (mmm * ONE_MIN);
          x += (hhh * ONE_HOUR);
          x += (dd * ONE_DAY);
  return  x;
}

bool checkIfRunning(int8_t tt, int8_t val){
  if(val == Cancel || val == Select){
    return 0;
  }else if(val > Select && val < Cancel){
    if(tt == 1 && t1Run) return 1;
    if(tt == 2 && t2Run) return 1;
    if(tt == 3 && t3Run) return 1;
    if(tt == 4 && t4Run) return 1;
    if(tt == 5 && t5Run) return 1;
    if(tt == 6 && t6Run) return 1;
  }
  return 0;
}

void print_timer(uint8_t tt, uint32_t totalSec){
  uint8_t dd, hhh, mmm, sss;
  dd = totalSec / ONE_DAY;
  uint16_t remainingSec = totalSec % ONE_DAY;
  hhh = remainingSec / ONE_HOUR;
  remainingSec = remainingSec % ONE_HOUR;
  mmm = remainingSec / ONE_MIN;
  sss = remainingSec % ONE_MIN;
  if(tt == 1)lcd.setCursor(2,1);
  if(tt == 2)lcd.setCursor(13,1);
  if(tt == 3)lcd.setCursor(2,2);
  if(tt == 4)lcd.setCursor(13,2);
  if(tt == 5)lcd.setCursor(2,3);
  if(tt == 6)lcd.setCursor(13,3);
  char buf_t[8];
  if(dd > 0){
    sprintf(buf_t, "D %02u:%02u", dd, hhh);
  }else if(hhh > 0 && hhh < 24){
    sprintf(buf_t, "H %02u:%02u", hhh, mmm);
  }else{
    sprintf(buf_t, "  %02u:%02u", mmm, sss);
  }
  lcd.print(buf_t);
  return;
}

void timerEnd(uint8_t tt){
  alarm = 1;
  if(tt == 1){lcd.setCursor(2,1);strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[EndTimer1])));}
  if(tt == 2){lcd.setCursor(13,1);strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[EndTimer2])));}
  if(tt == 3){lcd.setCursor(2,2);strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[EndTimer3])));}
  if(tt == 4){lcd.setCursor(13,2);strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[EndTimer4])));}
  if(tt == 5){lcd.setCursor(2,3);strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[EndTimer5])));}
  if(tt == 6){lcd.setCursor(13,3);strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[EndTimer6])));}
  lcd.print(buffer);
  return;
}

void updateTimers(void){
  if(alarm){
    tone(alarmPin,1047, 500);
    digitalWrite(led, !digitalRead(led));
  }
  if(clickMode == TimeDisp){
    updateTime();
  }
  if(t1Run){
    timer1 -= 1;
      if(timer1 > 0){
        print_timer(1, timer1);
      }else{
        t1Run = 0;
        timer1 = 0;
        timerEnd(1);
      }
  }
  if(t2Run){
    timer2 -= 1;
      if(timer2 > 0){
        print_timer(2, timer2);
      }else{
        t2Run = 0;
        timer2 = 0;
        timerEnd(2);
      }
  }
  if(t3Run){
    timer3 -= 1;
      if(timer3 > 0){
        print_timer(3, timer3);
      }else{
        t3Run = 0;
        timer3 = 0;
        timerEnd(3);
      }
  }
  if(t4Run){
    timer4 -= 1;
      if(timer4 > 0){
        print_timer(4, timer4);
      }else{
        t4Run = 0;
        timer4 = 0;
        timerEnd(4);
      }
  }
  if(t5Run){
    timer5 -= 1;
    if(timer5 > 0){
        print_timer(5, timer5);
      }else{
        t5Run = 0;
        timer5 = 0;
        timerEnd(5);
      }
  }
  if(t6Run){
    timer6 -= 1;
    if(timer6 > 0){
        print_timer(6, timer6);
      }else{
        t6Run = 0;
        timer6 = 0;
        timerEnd(6);
      }
  }
  return;
}
