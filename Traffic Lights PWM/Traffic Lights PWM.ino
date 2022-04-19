#include <Arduino.h>


// numbers are GPIO Pins 
const int ledPin1 = 13; 
const int ledPin2 = 0; 
const int ledPin3 = 16;

void setup() {


}

void loop() {
 // PWM duty cycle
int dutyCycle;

// red light
dutyCycle = 255;
analogWrite(ledPin1, dutyCycle );
delay(5000);
dutyCycle = 0;
analogWrite(ledPin1, dutyCycle );
delay(1);

// green light
dutyCycle = 255;
analogWrite(ledPin3, dutyCycle );
delay(5000);
dutyCycle = 0;
analogWrite(ledPin3, dutyCycle );
delay(1);

// orange light
dutyCycle = 255;
analogWrite(ledPin2, dutyCycle );
delay(2000);
dutyCycle = 0;
analogWrite(ledPin2, dutyCycle );
delay(1);

}
