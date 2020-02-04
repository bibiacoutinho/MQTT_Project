# MQTT_Project
## Descrição
Projeto utilizando Python e NodeMCU para comunicação MQTT.

###### Arquivo pub_client
Publica mensagem "ON" ou "OFF" para ligar/desligar LED.

###### Arquivo sub_client
Recebe mensagens "LED_ON" ou "LED_OFF" para informar status do LED.

###### Arquivo device
Firmware do NodeMCU ESP8266 que subscreve comandos e publica status do LED ao pressionar FLASH button.

## Pré-requisitos
- Python 2.7+, biblioteca paho-mqtt;
- Arduino 1.8.9, bibliotecas ESP8266WiFi.h, PubSubClient.h e esp8266 2.5
###### Instalando paho-mqtt
```
pip install paho-mqtt
```

###### Instalando ESP8266WiFi.h
Arduino > Preferências > URLS adicionais : http://arduino.esp8266.com/stable/package_esp8266com_index.json > OK

###### Instalando PubSubClient.h
Download da pasta PubSubClient-2.7.0 e inserir na pasta "libraries" do Arduino

###### Instalando esp8266
Arduino > Ferramentas > Gerenciar Bibliotecas > Digitar: esp8266 > Selecionar versão 2.5 > Instalar

###### Configurando placa
Arduino > Ferramentas > Placas > NodeMCU 1.0 (ESP-12E Module)
