#include <ArduinoWiFiServer.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "Gagnuss Office 1"; // home wifi
const char* password ="96450168"; // home password 
uint8_t retries=0;


void setup() {
  // serial initiation
  Serial.begin(115200);
  delay(100);
  Serial.println();

  // wifi connection 
  WiFi.begin(ssid, password);
  Serial.print("Connecting To ");
  Serial.print(ssid);
  Serial.println("...");

  // waiting for connecting with a 20 second timeout
  while(WiFi.status()!=WL_CONNECTED && retries<20){
    Serial.print(".");
    retries++;
    delay(1000);
  }
// timeout 
  Serial.println();
  if (retries==20) {
Serial.print("Unable to connect to ");
Serial.println(ssid);
  }
// success
if(WiFi.status()==WL_CONNECTED){
  Serial.println("Successfully Connected...");
Serial.println(ssid);
Serial.print("IP = ");
Serial.println(WiFi.localIP());
}
}

void loop() {
  // checking for the connectiong
if (WiFi.status()==WL_CONNECTED){
  Serial.println("Connected...");
  delay(30000); // check for connection every 30 seconds
} else {
  Serial.print("Trying to connect with ");
  Serial.print(ssid);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Successfully Connected to ");
  Serial.println(ssid);
  Serial.print("IP = ");
  Serial.println(WiFi.localIP());
}
}