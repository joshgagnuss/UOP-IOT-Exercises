/* 
Josh Gagnuss

software created to take in and evaluate weather inputs to remotely operate turf breeze fans 
on the golf course without the need of human input. 

*/

// required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

//device access 
const char* ssid = "Remote-Turfbreeze";
const char* password = "password";

// DHT input pin & type 
#define DHTInput 13
#define DHTTYPE DHT22 
DHT dht(DHTInput, DHTTYPE);

// LED Output
#define LED D5

// create LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// initiate temperature & humidity
float temperature = 0.0;
float humidity = 0.0;

// initiate server on port 80
AsyncWebServer server(80);

// keep track between DHT updates
unsigned long previousMilliseconds = 0;

// DHT sensor update intervals (20 Seconds)
const long interval = 5000;

// UI
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Remote Turf Breeze Monitor</h2>
  <p>
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// place values into html when readings are available 
String processor(const String& var) {
  //Serial.println(var); #uncomment if debugging required
  if (var == "TEMPERATURE"){
    return String(temperature);
  } else if (var == "HUMIDITY") {
    return String(humidity);
  }
  return String();
}

void setup() {
 Serial.begin(115200); // for any debugging purposes
 dht.begin(); // activate dht sensor

// activate lcd display
 lcd.begin(16,2);
 lcd.init();
 lcd.backlight();

 // initiate onboard LED for easier fault identification
 pinMode(2, OUTPUT); // stays solid until loop starts 
 pinMode(LED, OUTPUT);

 // display in monitor for activation purposes
 Serial.println("Activating Sensor");
 WiFi.softAP(ssid, password);
 // display IP address in serial monitor
 Serial.println(WiFi.softAPIP());

// lcd initalising text & IP
  lcd.clear(); 
  lcd.setCursor(2, 0); 
  lcd.print("Initialising");
  lcd.setCursor(2, 1); 
  lcd.print(WiFi.softAPIP());
  delay(5000);

 // routing for web page
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send_P(200, "text/html", index_html, processor);
 });

 // temperature request
 server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send_P(200, "text/plain", String(temperature).c_str());
 });

 // humidity request
 server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
   request->send_P(200, "text/plain", String(humidity).c_str());
 });

 // manual ovverride with button and trigger 


 // activate the server
 server.begin();
}

void loop() {
  // set millisecond counter
unsigned long currentMilliseconds = millis();


if (currentMilliseconds - previousMilliseconds >= interval){
  previousMilliseconds = currentMilliseconds; // saves the last time DHT values were read

// read the temperature (Celsius)
float newTemperature = dht.readTemperature();
float newHumidity = dht.readHumidity();
if (isnan(newTemperature) && isnan(newHumidity)) {
  Serial.println("Failure - Could not read values from sensor");
  lcd.clear(); 
  lcd.setCursor(2, 0); 
  lcd.print("Temperature");
  lcd.setCursor(2, 1); 
  lcd.print("Fault");
  delay(1000);
  //flashing the on-board light 5 times at .5sec intervals to indicate fault with temp & humidity sensor
  int count = 0;
  while (count ++ < 5){
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
} else {
  temperature = newTemperature;
  humidity = newHumidity;
  Serial.println(temperature);
  Serial.println(humidity);
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Tem: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1); 
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  // flashing on-board light 2 times at 1sec intervals to indicate operational
  int count =0;
  while (count ++ < 2) {
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    delay(2000);
  } 
} // esle statement
if (newTemperature >= 25) {
  digitalWrite(LED, HIGH);
} else {
  digitalWrite(LED, LOW);
}
} // if interval statement
} // loop

