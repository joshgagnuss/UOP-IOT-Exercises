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

const char* ap_ssid = "Gagnuss NodeMCU"; // broadcast
const char* ap_password ="password"; // password 

uint8_t max_connections=8; // limiting connections
int current_stations=0, new_stations=0;

void setup() {
  // serial initiation
Serial.begin(115200);
Serial.println();

if(WiFi.softAP(ap_ssid,ap_password,1,false,max_connections)==true){
  Serial.print("Access Point is Live With SSID: ");
  Serial.println(ap_ssid);
  Serial.println("Maximum Connections Allowed: ");
  Serial.println(max_connections);
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());
} else {
  Serial.println("Unable to go live");
}
}

void loop() {
  // checking station for connections & disconnections 
new_stations=WiFi.softAPgetStationNum();

if (current_stations<new_stations) { // new connection
  current_stations=new_stations;
  Serial.print("New Device Connection, Total Connections: ");
  Serial.println(current_stations);
}

if (current_stations>new_stations) { // disconnection
  current_stations=new_stations;
  Serial.print("Device Disconnected, Total Connections: ");
  Serial.println(current_stations);
}

}















