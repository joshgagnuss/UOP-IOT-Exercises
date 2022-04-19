#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// initiate lCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED1 D5
#define LED2 D6

void setup() {
// LED Setup
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

// LCD Setup
  lcd.begin(16,2); 
  lcd.init(); 
  lcd.backlight(); 
}

void loop() {

digitalWrite(LED1, HIGH); 
 lcd.clear(); 
 lcd.setCursor(4, 0); 
 lcd.print("Blue On"); 
 delay(500);

 digitalWrite(LED1, LOW); 
 delay(100);


 digitalWrite(LED2, HIGH); 
 lcd.clear(); 
 lcd.setCursor(4, 0); 
 lcd.print("Red On"); 
 delay(500);

 digitalWrite(LED2, LOW); 
 delay(100);
}
