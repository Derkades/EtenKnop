#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "passwd.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWD;

const char* hostname = "192.168.1.100";
const int port = 1883;

const char* mqttUser = "etenKnop";
const char* mqttPassword = "z3Z4poX4vSov54SP3Rrz";
const char* mqttTopic = "iot/eten";

//const int buttonPin = 34;
const int ledRPin = 25;
const int ledGPin = 33;
const int ledBPin = 32;

void callback(char* topic, byte* payload, unsigned int length) {}

WiFiClient wifiClient;
PubSubClient client(hostname, port, callback, wifiClient);

void setup() {
  Serial.begin(115200);

  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT); 

  delay(200);

  digitalWrite(ledBPin, HIGH);
    
    WiFi.enableSTA(true);

    Serial.println("Verbinden met WiFi");
      
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(300);
    }
    
    Serial.println();
    Serial.println("Verbonden met WiFi");
    Serial.println("IP addres: ");
    Serial.println(WiFi.localIP());
    
    Serial.println("Verbinden met MQTT");
    
    char* clientId = "eten_knop";
    client.connect(clientId, mqttUser, mqttPassword);
    
    if (client.publish(mqttTopic, "knop")) {
      
      Serial.println("ok");

      delay(700);
      digitalWrite(ledBPin, LOW);
      digitalWrite(ledGPin, HIGH);
      
      while(true){
        delay(69);
      }
    } else {
      digitalWrite(ledBPin, LOW);
      Serial.println("Er is iets misgegaan");
      
      while (true){
        digitalWrite(ledRPin, LOW);
        delay(500);
        digitalWrite(ledRPin, HIGH);
        delay(500);
      }
  }
}

void loop() {
  delay(21);
}
