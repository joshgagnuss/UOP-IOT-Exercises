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

//device access 
const char* ssid = "Remote-Turfbreeze";
const char* password = "password";

// DHT input pin & type 
#define DHTInput 5 
#define DHTTYPE DHT11 
DHT dht(DHTInput, DHTTYPE);

// initiate temperature & humidity
float temperature = 0.0;
float humidity = 0.0;

// initiate server on port 80
AsyncWebServer server(80);

// keep track between DHT updates
unsigned long previousMilliseconds = 0;

// DHT sensor update intervals (20 Seconds)
const long interval = 10000;

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
String processor(const String& var){
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

 // initiate onboard LED for easier fault identification
 pinMode(2, OUTPUT); // stays solid until loop starts 

 // display in monitor for activation purposes
 Serial.println("Activating Sensor");
 WiFi.softAP(ssid, password);
 // display IP address in serial monitor
 Serial.println(WiFi.softAPIP());

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
if (isnan(newTemperature)) {
  Serial.println("Failure - Could not read temperature values from sensor");
  //flashing the on-board light 5 times at .5sec intervals to indicate fault
  int count = 0;
  while (count ++ < 5){
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
    
} else {
  temperature = newTemperature;
  Serial.println(temperature);
  // flashing on-board light 2 times at 1sec intervals to indicate operational
  int count =0;
  while (count ++ < 2) {
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    delay(2000);
  }
    
}

// read the humidity
float newHumidity = dht.readHumidity();
if (isnan(newHumidity)) {
  Serial.println("Failure - Could not read humidity from sensor");
  //flashing the on-board light 4 times at .5sec intervals to indicate fault
  int count = 0;
  while (count ++ < 4){
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
} else {
  humidity = newHumidity;
  Serial.println(humidity);
  // flashing on-board light 2 times at 1sec intervals to indicate operational
  int count =0;
  while (count ++ < 2) {
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(2, LOW);
    delay(2000);
  }
}
}
}

