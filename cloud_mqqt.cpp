
#ifdef ESP32 
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <PubSubClient.h>
#include "cloud_mqqt.h"
#include "debug2.h"
#include "credentials.h"

// local...
static WiFiClient _espClient;
static PubSubClient _client(_espClient);

MQQHandler::MQQHandler() {
  _isInitialized = false;
}

void MQQHandler::Init(const char * clientName) {
    char buf[128];

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        SerialPrintLn("MQQHandler::Init", "Connecting to WiFi..");
    }
    
    SerialPrintLn("MQQHandler::Init", "Connected to the WiFi network");
    _client.setServer(mqttServer, mqttPort);

    while (!_client.connected()) {
        if (_client.connect(clientName, mqttUser, mqttPassword)) {
            SerialPrintLn("MQQHandler::Init", "Connected to MQTT");
        } else {
            sprintf(buf, "Failed To Connect To MQTT with State: %d", _client.state());
            SerialPrint("MQQHandler::Init", buf);
            delay(2000);
        }
    }

   _isInitialized = true;  
}


void MQQHandler::SetCallback(MQTT_CALLBACK_SIGNATURE)
{
    _client.setCallback(callback);
}   

void MQQHandler::Subscribe(const char * topic)
{
    _client.subscribe(topic);  
}

void MQQHandler::Publish(const char * topic, const char * msg) {
    if(_isInitialized) {
      _client.publish(topic, msg);
    }
}

void MQQHandler::Update() {
    if(_isInitialized) {
      _client.loop();
    }
}

// singleton..
MQQHandler MQQ;
