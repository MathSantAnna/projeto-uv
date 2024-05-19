#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <iostream>
#include <random>

// DEFINIÇÕES DE PINOS
#define pinLedVermelho 12
#define pinLedAmarelo  2
#define pinLedVerde    4

#define pinSensorUV    A0
#define divisor        20

// DEFINIÇÕES
#define liga    HIGH
#define desliga LOW

#define DEBUG

// Definições de conexão WiFi e MQTT
const char* ssid = "Theo";
const char* password = "pandora123";
const char* mqtt_server = "test.mosquitto.org";

// Cliente WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Protótipos de funções
void setup_wifi();
void reconnect();

// Tópico MQTT para envio de mensagens
const char* uv_topic = "home/outdoor/uvindex";
const char* uv_hight_topic = "home/outdoor/uvindexhight";

const char* uv_low_message = "Aproveite o sol com tranquilidade, mas não esqueça do protetor.";
const char* uv_medium_message = "Use protetor solar, o índice de raios UV está moderado.";
const char* uv_hight_message = "Cuidado extra ao sol, índice de raios UV está alto.";
const char* uv_danger_message = "Alerta máximo de raios UV! Proteja-se completamente.";

// std::mt19937 rng(std::random_device{}());

// Define o intervalo desejado (de 0 a 10)
// std::uniform_int_distribution<int> dist(0, 10);


void setup() {
  Serial.begin(115200);
  
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinSensorUV, INPUT);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int leituraUV = analogRead(pinSensorUV);
  byte indiceUV = map(leituraUV, 0, 1023, 0, 10);

  /* 
    Randor number to test dashboard
    
    // Gera um número aleatório no intervalo especificado
    int num_aleatorio = dist(rng);
    byte indiceUV = num_aleatorio;
  */

  if (indiceUV >= 8){ // SE O INDICE FOR MAIOR OU IGUAL A 8 LIGA O LED VERMELHO
    
    digitalWrite (pinLedAmarelo , desliga);
    digitalWrite (pinLedVerde , desliga);
    digitalWrite (pinLedVermelho , liga);

    if (client.connected()) {
      client.publish(uv_hight_topic, uv_danger_message);
    }
    
  } else if (indiceUV >= 6){ // SE O INDICE FOR MENOR QUE 8 E MAIOR OU IGUAL A 6 LIGA O LED AMARELO E VERMELHO
    
    digitalWrite (pinLedAmarelo , liga);
    digitalWrite (pinLedVerde , desliga);
    digitalWrite (pinLedVermelho , liga);

    if (client.connected()) {
      client.publish(uv_hight_topic, uv_hight_message);
    }
    
  } else if (indiceUV >= 3){ // SE O INDICE FOR MENOR QUE 6 E MAIOR OU IGUAL A 3 LIGA O LED AMARELO
    
    digitalWrite (pinLedAmarelo , liga);
    digitalWrite (pinLedVerde , desliga);
    digitalWrite (pinLedVermelho , desliga);

    if (client.connected()) {
      client.publish(uv_hight_topic, uv_medium_message);
    }
    
  } else { // SE O INDICE FOR MENOR QUE 3 LIGA APENAS O LED VERDE
    
    digitalWrite (pinLedAmarelo , desliga);
    digitalWrite (pinLedVerde , liga);
    digitalWrite (pinLedVermelho , desliga);
    if (client.connected()) {
      client.publish(uv_hight_topic, uv_low_message);
    }
  }

  if (client.connected()) {
    client.publish(uv_topic, String(indiceUV).c_str());
  }
  // Manipule outras condições e LEDs conforme necessário.
  
  delay(2000);  // Aumentando o tempo de delay para 2 segundos.
}

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("uvSensorNode")) {
      Serial.println("connected");
      // Se precisar se inscrever em tópicos faça isso aqui:
      // client.subscribe("some/topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}