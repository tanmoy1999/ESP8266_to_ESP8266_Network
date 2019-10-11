/*
 * THIS IS A SERVER SIDE CODE
 * 
 * YOU NEED TO CONNECT AN LED TO THE D2 PIN
 * TO KNOW THE DATA IS TRANSMITTING AND RECEIVING
 * PROPERLY. 
 * 
 * 
 * Tanmoy Munshi
 * email id: tanmoymunshi1999@gmail.com
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "ENTER YOUR WIFI SSID";
const char* password = "ENTER YOUR WIFI PASSWORD";
int max_connection = 8;           // MAXIMUM NO. OF CLIENT CAN BE CAONNECTED IS 8
int LED  = D2;

//IP Declaration

IPAddress staticIP(10,10,10,1); // IP address from Admin pannel 
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);


int httpCode;

HTTPClient http;

ESP8266WebServer server(80); //Server on port 80


//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
void LightOn() {
  server.send(200, "text/plain", "LIGHT ON" );
  Serial.println("LIGHT ON");
  digitalWrite(D2, HIGH);               
}
void LightOff() {
  server.send(200, "text/plain", "LIGHT OFF" );
  Serial.println("LIGHT OFF");
  digitalWrite(D2, LOW);;               
}

//===============================================================
//                  SETUP
//===============================================================

void setup(void){
 
  Serial.begin(115200);
  Serial.println("");
  WiFi.mode(WIFI_AP);                                 //WIFI MODE USING Only Access point
  WiFi.softAP(ssid, password, 1, false, max_connection); 
  WiFi.softAPConfig(staticIP, gateway, subnet);      //Starts hotspot removing password will disable security
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());  // NUMBER OF CLIENT CONNECTED


  IPAddress myIP = WiFi.softAPIP();                  //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
   pinMode(D2, OUTPUT);
  
   delay(1000);
  
   server.on("/", handleRoot);                      //Which routine to handle at root location
   server.on("/LightOn", LightOn);
   server.on("/LightOff", LightOff);
   server.begin();                                  //Starting server
   Serial.println("HTTP server started");
}


void loop(void){

      server.handleClient();          //Handle client requests
} 
