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

#define WIFI_SSID "Bacom"
#define WIFI_PASSWORD "potatosoup"

#define UDP_HOST "255.255.255.255"
#define UDP_PORT 37548

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
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
    delay(100);
    Serial.print(".");
  }
   
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_BUILTIN,HIGH);
  
}

void SendPacket(){
  WiFiUDP UDP;
  /* Start UDP on port */
  UDP.begin(UDP_PORT);
  UDP.beginPacket(UDP_HOST,UDP_PORT);
  UDP.write(CHAVE_SECRETA);
  UDP.endPacket();
  delay(1000);
}


void loop() {
  
  SendPacket();
  
}
