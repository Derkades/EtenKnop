#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char* ssid = "aivd_afluisterbus_2a98e";
const char* password =  "zonderdraadje_iot";

const char* hostname = "192.168.2.1";
const int port = 1883;

const char* mqttUser = "etenKnop";
const char* mqttPassword = "z3Z4poX4vSov54SP3Rrz";
const char* mqttTopic = "iot/eten";

const int buttonPin = 34;
const int ledRPin = 25;
const int ledGPin = 33;
const int ledBPin = 32;

void callback(char* topic, byte* payload, unsigned int length) {}

WiFiClient wifiClient;
PubSubClient client(hostname, port, callback, wifiClient);

void setup() {
  Serial.begin(115200);
  
  pinMode(buttonPin, INPUT);

  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT); 

  delay(200);

  digitalWrite(ledRPin, HIGH);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH){
    digitalWrite(ledRPin, LOW);
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
      digitalWrite(ledBPin, LOW);
      Serial.println("ok");

      digitalWrite(ledGPin, HIGH);
      delay(2500);
      digitalWrite(ledGPin, LOW);
      
      while (true){
        digitalWrite(ledBPin, LOW);
        delay(500);
        digitalWrite(ledBPin, HIGH);
        delay(500);
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

  delay(100);
}
