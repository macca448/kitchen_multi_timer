void updateMainMenu(int8_t val){
  char buf[3];
  strcpy_P(buffer, (char *)pgm_read_word(&(mainMenu[val])));
  sprintf(buf,"T:%i",activeTimer);
  lcd.setCursor(0, 0);
  lcd.print(buffer);
  lcd.setCursor(17, 0);
  lcd.print(buf);
}

void setValue(uint8_t val, int8_t tt){ 

  if(clickMode == ChooseMinValue){
    if(tt == 1){
      t1Min = val;
    }else if(tt == 2){
      t2Min = val;
    }else if(tt == 3){
      t3Min = val;
    }else if(tt == 4){
      t4Min = val;
    }else if(tt == 5){
      t5Min = val;
    }else if(tt == 6){
      t6Min = val;
    }
  }else if(clickMode == ChooseSecValue){
    if(tt == 1){
      t1Sec = val;
    }else if(tt == 2){
      t2Sec = val;
    }else if(tt == 3){
      t3Sec = val;
    }else if(tt == 4){
      t4Sec = val;
    }else if(tt == 5){
      t5Sec = val;
    }else if(tt == 6){
      t6Sec = val;
    }
  }else if(clickMode == ChooseHourValue){
    if(tt == 1){
      t1Hour = val;
    }else if(tt == 2){
      t2Hour = val;
    }else if(tt == 3){
      t3Hour = val;
    }else if(tt == 4){
      t4Hour = val;
    }else if(tt == 5){
      t5Hour = val;
    }else if(tt == 6){
      t6Hour = val;
    }
  }else if(clickMode == ChooseDayValue){
    if(tt == 1){
      t1Day = val;
    }else if(tt == 2){
      t2Day = val;
    }else if(tt == 3){
      t3Day = val;
    }else if(tt == 4){
      t4Day = val;
    }else if(tt == 5){
      t5Day = val;
    }else if(tt == 6){
      t6Day = val;
    }
  }else if(clickMode == ChooseTimerValue){
    char buf[3];
    lcd.setCursor(17, 0);
    activeTimer = val +1;
    sprintf(buf,"T:%i",activeTimer);
    lcd.print(buf);
  }
    if(tt == 1 && !t1Run){
      timer1 = configTimer(t1Day, t1Hour, t1Min, t1Sec);
      print_timer(tt, timer1);
    }else if(tt == 2 && !t2Run){
      timer2 = configTimer(t2Day, t2Hour, t2Min, t2Sec);
      print_timer(tt, timer2);
    }else if(tt == 3 && !t3Run){
      timer3 = configTimer(t3Day, t3Hour, t3Min, t3Sec);
      print_timer(tt, timer3);
    }else if(tt == 4 && !t4Run){
      timer4 = configTimer(t4Day, t4Hour, t4Min, t4Sec);
      print_timer(tt, timer4);
    }else if(tt == 5 && !t5Run){
      timer5 = configTimer(t5Day, t5Hour, t5Min, t5Sec);
      print_timer(tt, timer5);
    }else if(tt == 6 && !t6Run){
      timer6 = configTimer(t6Day, t6Hour, t6Min, t6Sec);
      print_timer(tt, timer6);
    }
}

void on_rotenc_rotated_ccw(void) {
 
  value--;
  timeOutCount = 0;

  if(clickMode == TimeDisp){
    if(lcdOFF){
      lcd.on();
      lcdOFF = 0;
    }
    clickMode = Menu;  
    value = Select;
  }

  if(value < 0){     
    if(clickMode == ChooseTimerValue)value = 5;
    if(clickMode == ChooseMinValue || clickMode == ChooseSecValue)value = 59;
    if(clickMode == ChooseHourValue)value = 23;
    if(clickMode == ChooseDayValue)value = 99;
    if(clickMode == Menu)value = 6;
  }

  if(PRINT == true){
    Serial.print("CCW\t");
    Serial.println(value);
  }

  if(clickMode == Menu){
    updateMainMenu(value);
  }else if(clickMode > Cancel && clickMode < Blank){
    setValue(value, activeTimer);
  }
}

void on_rotenc_rotated_cw(void) {
  
  value++;
  timeOutCount = 0;

  if(clickMode == TimeDisp){
    if(lcdOFF){
      lcd.on();
      lcdOFF = 0;
    }
    clickMode = Menu;  
    value = Select;
  }

  if(clickMode == Menu)value %= 7;
  if(clickMode == ChooseTimerValue)value %= 6;
  if(clickMode == ChooseMinValue || clickMode == ChooseSecValue)value %= 60;
  if(clickMode == ChooseHourValue)value %= 24;
  if(clickMode == ChooseDayValue)value %= 100;
  
  if(PRINT == true){
    Serial.print("CW\t");
    Serial.println(value);
  }
  
  if(clickMode == Menu){
    updateMainMenu(value);
  }else if(clickMode > Cancel && clickMode < Blank){
    setValue(value, activeTimer);
  }
}