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
#define RESPOSTA_SECRETA "Never gonna let you down"

#define WIFI_SSID "TesteAssento"
#define WIFI_PASSWORD "aaa3332929k"

#define UDP_HOST "255.255.255.255"
#define UDP_PORT 37548

#define MAX_ATTEMPTS 10
#define WAIT_TIME 5000 //mSECONDS

/* Pino D5 */
#define GPIO_SEAT 5

/* Pino D6 */
#define GPIO_BUZER 4


void SendPacket(WiFiUDP UDP){
  /* Start UDP on port */
  UDP.beginPacket(UDP_HOST,UDP_PORT);
  UDP.write(CHAVE_SECRETA);
  UDP.endPacket();
  delay(1000);
}

WiFiUDP UDP;
char packet[255];

void setup() {
  
  UDP.begin(UDP_PORT);
  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  Serial.println();
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GPIO_BUZER, OUTPUT);
  pinMode(GPIO_SEAT, INPUT);

  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(GPIO_BUZER,HIGH);

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



}

bool LockComputer(){
  
  for (int attempt_number = 0; attempt_number < MAX_ATTEMPTS; attempt_number++)
  {
    Serial.println("Sending signal to broadcast...");
    SendPacket(UDP);
    Serial.println("Waiting for a computer to answer...");
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

      if (String(packet) == RESPOSTA_SECRETA)
      {
        Serial.println("Correct response. DeepSleep activated");
        return true;
      }
      Serial.println("Wrong response. Continuing to wait...");
    }else{
      Serial.println("No packets received. Continuing to wait....");
    }
  }
  return false;


}

void AnnoyUser(){
    digitalWrite(GPIO_BUZER,LOW);
    delay(800);
    digitalWrite(GPIO_BUZER,HIGH);
    delay(800);
}

uint32_t initialTime, currentTime;

void loop() {

  
  /* Keeps program stuck on deepsleep if user not up */
  Serial.println("User is seated.");
  while(digitalRead(GPIO_SEAT) == LOW){
    delay(5000);
    return;
  }
  
  Serial.println("User left. Waiting for its return...");
  
  initialTime = millis();
  Serial.println("Testing for him to come back...");
  
  /* Waits for five seconds */
  while(true){
    if (digitalRead(GPIO_SEAT)==LOW){
      Serial.println("He did!");
      return;
    }
    delay(100);
    currentTime = millis();
    if ((currentTime - initialTime) > 5000){
      break;
    }
  }

  Serial.println("User did not returned. Locking computer...");
  /* Tries to lock the computer, if it's not locked annoys user */
  if(!LockComputer()){
    Serial.println("Failed to lock computer. Annoying user..");
    while(digitalRead(GPIO_SEAT)==HIGH){
      Serial.println("ANNOYING....");
      AnnoyUser();
    }
    Serial.println("User returned after beying annoyed.");
    return;
  }  

  /* Confirms the user is seated one more time (or once if lock is succeded) before continuing loop */
  Serial.println("Locked computer. Waiting for him to come back.");
  while(digitalRead(GPIO_SEAT)==HIGH);

  
}
