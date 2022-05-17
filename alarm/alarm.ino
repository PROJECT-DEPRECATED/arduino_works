/**
 * LCD Alarm project
 * This source followed by General Public License 3.0v
 */

#include <LiquidCrystal.h>
#include <core_build_options.h>
#include <swRTC.h>

#define PIEZO 8
#define BUTTON 9

LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
int pin[6] = { A0, A1, A2, A3, A4, A5 };
swRTC rtc;
int tmp;

String low_than_tens(int time) {
    String str = "";
    if (time < 10) {
        str += "0";
        str += String(time % 10);
    } else {
        str += String(time);
    }

    return str;
}

String hour_format(int hour) {
    String str = "";
    if (hour > 12) {
        str += "PM";
        str += String(hour % 12);
    } else if (hour == 12) {
        str += "PM";
        str += String(hour);
    } else {
        str += "AM";
        str += String(hour);
    }
    
    return str;
}

void get_hour() {
    int hour = rtc.getHours();
    String str = hour_format(hour);
    
    lcd.print(str);
}

int check_define_alarm_time(int time) {
    if (time / 100 < 24 && time % 100 < 60) {
        Serial.println("Success");
        return time;
    }

    return 0;  
}

void led(int *pin, int delay_ms) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(pin[i], 1);
        delay(delay_ms);
        digitalWrite(pin[i], 0);
    }

    for (int i = 6; i >= 0; i--) {
        digitalWrite(pin[i], 1);
        delay(delay_ms);
        digitalWrite(pin[i], 0);
    }
}

void check_alert_time(int hour, int minute) {
    if (hour == rtc.getHours() && minute == rtc.getMinutes()) {
        analogWrite(PIEZO, 128);
        led(pin, 100);
    }
}

void setup() {                   
    lcd.begin(16, 2);
    lcd.clear();
  
    rtc.stopRTC();
    rtc.setTime(15, 13, 00);
    rtc.setDate(17, 05, 2020);
    rtc.startRTC();
  
    pinMode(PIEZO, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);

    for (int i = 0; i < 6; i++) {
        pinMode(pin[i], OUTPUT);
    }
    
    Serial.begin(9600);
}

void loop() {
    int day;
    lcd.setCursor(0, 0);

    get_hour();
    lcd.print(":");
    lcd.print(low_than_tens(rtc.getMinutes()));
    lcd.print(":");
    lcd.print(low_than_tens(rtc.getSeconds()));
    
    lcd.print("[");
    lcd.print(low_than_tens(rtc.getMonth()));
    lcd.print("/");
    lcd.print(low_than_tens(rtc.getDay()));
    lcd.print("]");

    lcd.setCursor(0, 1);

    lcd.print("Alarm ");
    lcd.print(hour_format(tmp / 100));
    lcd.print(":");
    lcd.print(low_than_tens(tmp % 100)); 

    lcd.print("               ");
    delay(1000);
  
    check_alert_time(tmp / 100, tmp % 100);
   
    if (!digitalRead(BUTTON)) {
        tmp = 0;
        day = 0;
        analogWrite(PIEZO, 0);
        Serial.println("Alarm clock initialize");
        Serial.println("AM0:00");
    }
  
    char days[4];
    int i = 0;
    if (Serial.available()) {
    while (Serial.available()) {
        days[i] = Serial.read();
        i++;
    }
    
    day = atoi(days);
    if (day / 100 >= 12) {
        Serial.print("PM");
        Serial.print((day / 100) - 12);
    } else {
        Serial.print("AM");
        Serial.print(day / 100);
    }
    
    Serial.print(":");
    if (day % 100 < 10)
        Serial.print("0");
        Serial.println(day % 100);
        tmp = check_define_alarm_time(day);
    }
}
