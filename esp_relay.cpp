#include <Arduino.h>
#include "esp_relay.h"

static byte relON[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to serial for open relay
static byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay

// Turns ESP8266 relay on/off
void espRelay_setState(int relayState)
{
  // save state of gpio pin (double use... led and relay on ESP Relay Board)
  // uses same pin as led.  So, shut off led
  int oldState = digitalRead(ESP_RELAY_PIN); 

  Serial.begin(SERIAL_BAUDRATE);
  if(relayState == 0)
      Serial.write(relOFF, sizeof(relOFF));      // turns the relay OFF
  else
      Serial.write(relON, sizeof(relON));       // turns the relay ON
  Serial.flush();
  delay(100);
  
  // command has been sent to relay.  Turn back on.
  pinMode(ESP_RELAY_PIN, OUTPUT);
  digitalWrite(ESP_RELAY_PIN, oldState);  
}
