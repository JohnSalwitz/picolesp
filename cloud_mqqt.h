#ifndef MQQ_HANDLER
#define MQQ_HANDLER

#include <Arduino.h>

#ifndef MQTT_CALLBACK_SIGNATURE
#if defined(ESP8266) || defined(ESP32)
#include <functional>
#define MQTT_CALLBACK_SIGNATURE std::function<void(char*, uint8_t*, unsigned int)> callback
#else
#define MQTT_CALLBACK_SIGNATURE void (*callback)(char*, uint8_t*, unsigned int)
#endif
#endif


class MQQHandler {
  
public:
  MQQHandler();
  void Init(const char *clientName);
  void Publish(const char *topic, const char *msg);
  void Update();
  void SetCallback(MQTT_CALLBACK_SIGNATURE);
  void Subscribe(const char *topic);
  
private:
  bool _isInitialized;
  
};

// singleton
extern MQQHandler MQQ;

#endif
