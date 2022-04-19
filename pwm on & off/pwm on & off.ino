#include <Arduino.h>

// GPIO Pin
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
for(int Duty_cycle = 0; Duty_cycle < 255; Duty_cycle++){
  analogWrite(ledPin, Duty_cycle);
  delay(1);
}

for(int Duty_cycle = 255; Duty_cycle > 0; Duty_cycle--){
  analogWrite(ledPin, Duty_cycle);
  delay(1);
}

}


