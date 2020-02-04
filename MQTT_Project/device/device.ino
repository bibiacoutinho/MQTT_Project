//Projeto de Blink Led utilizando protocolo MQTT e programa em python como client

//ESP
#include <ESP8266WiFi.h>
//MQTT
#include <PubSubClient.h>

//WIFI CONFIG
const  char * ssid = "TecSUS" ;
const  char * password = "2018@tecwifi" ;

//MQTT CONFIG
const String HOSTNAME  = "TecDevice"; //NOME DO DEVICE, deverá ter um nome unico.
const char * MQTT_COMMAND_TOPIC = "TecSUS/cmd"; //Topico onde o Device subscreve.
const char * MQTT_STATE_TOPIC = "TecSUS/leitura"; //Topico onde o Device publica.


//EXEMPO DE BROKERS MQTT GRATUITOS PARA TESTES https://github.com/mqtt/mqtt.github.io/wiki/public_brokers
const char* MQTT_SERVER = "test.mosquitto.org"; //IP ou DNS do Broker MQTT

// Credenciais ao broker mqtt. Caso nao tenha AUTH, coloque em false.
#define MQTT_AUTH false
#define MQTT_USERNAME "CAn3Y2Ml3hkgzqOsGpQSNtfqW58la53Bwhui94u09C6ySLQmYw4zN8Oz3KI4FCt1"
#define MQTT_PASSWORD "CAn3Y2Ml3hkgzqOsGpQSNtfqW58la53Bwhui94u09C6ySLQmYw4zN8Oz3KI4FCt1"

//DEFINIR PIN DO LED E FLASH BUTTON
int ledpin = 5; //D1 (gpio5)
int button = 0; //FLASH (gpio0)


WiFiClient wclient;
PubSubClient client(MQTT_SERVER, 1883, wclient);

//INICIAR A LIGAÇÃO WIFI
void LigarWifi() {

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  Serial.print("\nA tentar ligar ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(String("\nLigado a rede: (") + ssid + ")" );
}

//INICIAR O MQTT
//Verifica se o estado da ligação está ativa e se não estiver tenta conectar-se
bool checkMqttConnection() {
  if (!client.connected()) {
    if (MQTT_AUTH ? client.connect(HOSTNAME.c_str(), MQTT_USERNAME, MQTT_PASSWORD) : client.connect(HOSTNAME.c_str())) {
      Serial.println("Ligado ao broker mqtt " + String(MQTT_SERVER));
      //SUBSCRIÇÃO DE TOPICOS
      client.subscribe(MQTT_COMMAND_TOPIC);
    }
  }
  return client.connected();
}

void setup() {
  Serial.begin(115200);

  //definir gpio5 como output e flash como input
  pinMode(ledpin, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  //Conecta a rede wifi criada
  LigarWifi();
  client.setCallback(callback); // resposta as mensagens vindas do MQTT
}

//Chamada de recepção de mensagem
void callback(char* topic, byte* payload, unsigned int length) 
{


  String payloadStr = "";
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }
  String topicStr = String(topic);

  if (topicStr.equals(MQTT_COMMAND_TOPIC)) 
  { //TÓPICO QUE O DEVICE SUBESCREVE
    if (payloadStr.equals("ON")) 
    {
      digitalWrite(ledpin, HIGH);
      Serial.print("LED LIGOU");

    }
    else if (payloadStr.equals("OFF")) 
    {
      digitalWrite(ledpin, LOW);
      Serial.print("LED DESLIGOU");
    }

  }

}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    if (checkMqttConnection()) 
    {
      client.loop();
    }
  }
  
  if (digitalRead(button)==0) //se FLASH for pressionado
  {
    if (digitalRead(ledpin)==1) //se o LED estiver aceso
    {
      client.publish("TecSUS/leitura", "LED_ON"); //publica "ON"
      
    }
    else 
    {
      client.publish("TecSUS/leitura", "LED_OFF"); //publica "OFF"
    }
    delay(500);
  }
}
