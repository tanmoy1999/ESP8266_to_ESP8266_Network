/*
 * THIS IS A CLIENT SIDE CODE
 * 
 * YOU NEED TO CONNECT A SENSOR TO THE ANALOG INPUT OF
 * THE ESP8266 AT A0 PIN. 
 * eg: IF CONNECTING LDR THEN CONNECT ONE TERMINAL TO A0 
 *     PIN AND ANOTHER TERMINAL TO Vin PIN
 *     
 * Tanmoy Munshi
 * email id: tanmoymunshi1999@gmail.com
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "ENTER YOUR WIFI SSID";
const char* password = "ENTER YOUR WIFI PASSWORD";


IPAddress ip(10,10,10,55); 
IPAddress gateway(10,10,10,1); 
IPAddress subnet(255,255,255,0);

const int analogValue = A0;
int inputValue  = 0;



ESP8266WebServer server(80);
void handleRoot() {
   server.send(200, "text/html", "message");
   
}


void setup() {
  server.on("/", handleRoot);               
                                            /************************************
                                               WiFi establishment and connection
                                            ************************************/

  server.begin();
    Serial.begin(115200);
    delay(100);
    WiFi.config(ip,gateway,subnet);
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] hold \n", t);
        Serial.flush();
        delay(1000);
    }
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(true);
    WiFi.begin(ssid,password);
    if(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
    
    Serial.println("CONNECTED");
  }
 pinMode(analogValue,INPUT);
   
}

void loop() {
    
  server.handleClient();    //Handle client requests

                            // wait for WiFi connection check
    if((WiFi.status() == WL_CONNECTED)) {
        inputValue = analogRead(analogValue);
        
        HTTPClient http;    
        if(inputValue == 1024)      //LDR Value 1024 OR HIGH   YOU CAN CHANCE THE SENSOR VALUE HERE
        {  
        
           http.begin("http://10.10.10.1/LightOn");
          Serial.println("LightOn");
          int httpCode = http.GET();
           http.end();
        } 

        else                      //LDR VALUE LESS THAN 1024
        {
          http.begin("http://10.10.10.1/LightOff");
          Serial.println("LightOff");
          int httpCode= http.GET();
          http.end();
        }       
    }    
}
