#include <Arduino.h>

#include "led_status.h"
#include "debug2.h"

// forward...
static int _previousRate = -1;
static int _sleepTimer = 0;
static int _sleepTime = 0;

void ledStatus_setup() 
{  
    pinMode(LED_STATUS_PIN, OUTPUT);
    digitalWrite(LED_STATUS_PIN, LOW);
    ledStatus_setRate(60);
}


void ledStatus_setRate(int beatsPerMinute)
{
  if((beatsPerMinute != _previousRate) && (beatsPerMinute > 0))
  {
    _previousRate = beatsPerMinute;
     float secondsPerBeat = 60.0f / (float)beatsPerMinute;
      // double speed (so whole period)
     _sleepTime = _sleepTimer =  (int)(secondsPerBeat * 1000.0f / 2.0f);
  }
}

// returns if normal processing.  (False if an error)
void ledStatus_loop(int deltaTime)
{ 
  if(_sleepTime > 0) 
  {  
      if(_sleepTimer == 0)
      {
        int state = digitalRead(LED_STATUS_PIN); 
        digitalWrite(LED_STATUS_PIN, !state);  
        _sleepTimer = _sleepTime;
      }
      else
      {
        _sleepTimer = max(_sleepTimer - deltaTime, 0);
      }
  }
}
