/**
  Controlador do Assento de Ocupação inteligente

  Código do microcontrolador NodeMCU 1.0 (ESP-12E Module)

*/

/* Importação das bibliotecas usadas */

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <WiFiUdp.h>

#define CHAVE_SECRETA "Never gonna give you up"

#define WIFI_SSID "Perterson"
#define WIFI_PASSWORD "23021991"

#define UDP_HOST "255.255.255.255"
#define UDP_PORT 37548

#define MAX_ATTEMPTS 10
#define WAIT_TIME 5000 //mSECONDS

#define GPIO_SEAT 5
#define GPIO_BUZER 4

void SendPacket(WiFiUDP UDP){
  /* Start UDP on port */
  UDP.beginPacket(UDP_HOST,UDP_PORT);
  UDP.write(CHAVE_SECRETA);
  UDP.endPacket();
  delay(1000);
}


void setup() {
  
  char packet[255];
  WiFiUDP UDP;
  UDP.begin(UDP_PORT);
  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  Serial.println();
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPIO_BUZER, OUTPUT);
  pinMode(GPIO_SEAT, INPUT);
  
  digitalWrite(LED_BUILTIN,LOW);
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
     
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
   
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_BUILTIN,HIGH);

  delay(WAIT_TIME);

  if (digitalRead(GPIO_SEAT) == HIGH)
  {
    Serial.println("DeepSleep activated");
    ESP.deepSleep(0);
  }
    

  // Waiting a response

  for (int attempt_number = 0; attempt_number < MAX_ATTEMPTS; attempt_number++)
  {
    delay(500);
    int packetSize = UDP.parsePacket();
 
    if (packetSize) {
      Serial.print("Received packet! Size: ");
      Serial.println(packetSize); 
      int len = UDP.read(packet, 255);
      if (len > 0)
      {
        packet[len] = '\0';
      }
      Serial.print("Packet received: ");
      Serial.println( String(packet) );

      if (String(packet).substring(0, len - 2) == "Never Gonna Let You Down")
      {
        Serial.println("DeepSleep activated");
        ESP.deepSleep(0);
      }
      
    }
  
    SendPacket(UDP);
  }
  
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
  
}