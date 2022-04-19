#include <Arduino.h>

// GPIO Pin
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
int dutyCycle;

dutyCycle = 255;
analogWrite(ledPin, dutyCycle );
delay(5000);
dutyCycle = 155;
analogWrite(ledPin, dutyCycle);
delay(5000);
dutyCycle = 10;
analogWrite(ledPin, dutyCycle);
delay(5000);
}
