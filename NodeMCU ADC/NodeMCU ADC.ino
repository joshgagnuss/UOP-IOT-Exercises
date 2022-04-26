// ESP8266 chips can only read up to 1v 
// you need 2 x restors 100ohm & 220ohm



const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot

void setup() {
  // initialize serial communication at 115200
  Serial.begin(115200);
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
 
  // print the readings in the Serial Monitor
  Serial.println("sensor = ");
  Serial.println(sensorValue);
  
  delay(10000);
}