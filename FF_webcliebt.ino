/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include "analogmuxdemux.h"
#define READPIN A0 // What analog input on the arduino do you want?

// how many input pins are you going to use on the Muxer, this example uses three
#define NO_PINS 8 

AnalogMux amux(16,5,4, READPIN);

const char* ssid     = "MYHOME";
const char* password = "Buka1609";

const char* host = "myiotsatu.sjtsmart.com";


void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
   amux.SelectPin(0);
        uint16_t reading = amux.AnalogRead();
 Serial.print(reading);
 Serial.print("  ");
  amux.SelectPin(1);
        uint16_t reading1 = amux.AnalogRead();
 Serial.print(reading1);
 Serial.print("  ");
   amux.SelectPin(2);
        uint16_t reading2 = amux.AnalogRead();
 Serial.print(reading2);
 Serial.print("  ");
   amux.SelectPin(3);
        uint16_t reading3 = amux.AnalogRead();
 Serial.print(reading3);
 Serial.print("  ");
   amux.SelectPin(4);
        uint16_t reading4 = amux.AnalogRead();
 Serial.print(reading4);
 Serial.print("  ");
   amux.SelectPin(5);
        uint16_t reading5 = amux.AnalogRead();
 Serial.print(reading5);
 Serial.println("  ");


  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/add.php";
 
  url += "?ff01=";
  url += reading;
  url += "&ff02=";
  url += reading1;
    url += "&ff03=";
  url += reading2;
    url += "&ff04=";
  url += reading3;
    url += "&ff05=";
  url += reading4;
    url += "&ff06=";
  url += reading5;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}

