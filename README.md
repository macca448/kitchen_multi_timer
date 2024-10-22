# Kitchen Multi-Timer
<br>

## Features:

1. Up to six (6) independant 100 day timers
2. Counts in seconds using RTC library function
3. LCD 2004 Display (4 lines with 20 characters per line)
4. Menu auto switch's to Date/Time after two(2) minutes of inactivity. This is an RTClib String function
5. Screen save after thirty(30) minutes of inactivity
6. Auto screen on by turning encoder knob
7. Multi-function button actions
<br>

## Using the Multi-Timer:
1. In the first level of the menu displayed at the far right is the active timer IE: 01
3. Rotate the knob and select which time value you wish to update IE SET MINUTES
4. Short buttton press and the display will change to "SELECT MIN  T:01"
5. Turning the knob will will update "1:" timer values (0 - 59)
6. Short press stores that value
7. Repeat steps 1 to 5 if you wish to set other values (Day's (1 - 99), Hour's (1 - 23) and Seconds (1 - 59)
8. When Days are greater than zero the timer will have a "D" prefix IE "1:D 01:00 being a days and hours readout
9. The timer will auto select three different readout modes depending on timer duration
10. When Days are zero but Hour's are greater than zero the timer will have a "H" prefix IE "1:H 01:00 being a hours and minutes readout
11. If there is no alpha prefix then the display is minutes and seconds
12. Turn knob to "START TIMER" and short press will start the active timer displayed at the far right on line 1
13. Once the timer has been started you can't change it but you can select "Cancel Timer" then short press and you will cancel the active timer
14. When a timer has completed " END T1" is displayed, the buzzer starts and a led blinks.
15. A Long button press (more than 750mS) to stop the alarm
16. If you didn't cancel a timer your original values will run it again by just selecting "START TIMER" and pressing the button
17. To setup another timer turn knob to "SELECT TIMER     0X" and a short press to enter select mode
18. Turn the knob to select a new active timer. "SELECT TIMER T:0X" is the curren timer and the far right is the new timer
19. Short press to enable new active timer

