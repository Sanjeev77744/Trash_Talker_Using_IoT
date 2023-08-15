#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include "initial.h"
//#include "lcd.h"

#define motor_positive_pin 4
#define motor_negative_pin 5
#define green_led 6
#define red_led 7



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  digitalWrite(motor_positive_pin, HIGH);
  digitalWrite(motor_negative_pin, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);
  pinMode(motor_positive_pin, OUTPUT);
  pinMode(motor_negative_pin, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("DRIVER BEHAVIOUR ");
  lcd.setCursor(5, 1);
  lcd.print("MONITORING");
  attachInterrupt(digitalPinToInterrupt(CRASH_SENSOR), crash_ISR, HIGH);
  pinMode(GAS_SENSOR, INPUT);
  delay(100);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (CRASH_FLAG == true) {
    CRASH_FLAG = false;
    Serial.println("ACCIDENT");
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("ACCIDENT");
    digitalWrite(motor_positive_pin, LOW);
    digitalWrite(motor_negative_pin, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, HIGH);
    while (1);
  }

  GAS_DATA = digitalRead(GAS_SENSOR);
  Serial.println(GAS_DATA);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("G:");
  lcd.print(GAS_DATA);


  if (GAS_DATA == 0) {
    lcd.setCursor(0, 1);
    lcd.print("ALCOHOL detected");
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, HIGH);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("No Gas detected");
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, LOW);
  }
  delay(100);
}


void crash_ISR() {
  CRASH_FLAG = true;
}