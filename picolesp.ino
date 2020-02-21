LCD
#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include "settings.h"
#include "debug2.h"
#include "logger.h"
#include "led_status.h"
#include "static_storage.h"
#include "picol_glue.h"
#include "cloud_mqqt.h"
#include "subscriptions.h"

const int _picoltime = 1000 / 20;            // frames per seconds (in ms)
static long _picolTimer;

void setup()
{
  const char *backgroundScript;

#ifdef ESP32 
  Serial.begin(115200);
#else
  Serial.begin(9600);
#endif
  
  SerialPrintLn("MQQ Init...");

  MQQ.Init(ESP_NAME);
  logger_post(LogLevelType::info, "Connected"); 

  
  SerialPrintLn("SubscriptionsInit...");
  SubscriptionsInit();

  // led blinker...
  SerialPrintLn("ledStatus_setup...");
  ledStatus_setup(); 

  SerialPrintLn("StaticStorage_Init...");
  StaticStorage_Init(default_backgroundScript);
  backgroundScript = StaticStorage_Read();

	SerialPrintLn("Setup Picol With Default Script: ");
  SerialPrintLn("-------------------------------------");
  SerialPrintLn(backgroundScript);
  SerialPrintLn("-------------------------------------");
  PicolGlue.setup(backgroundScript);
  _picolTimer = (long)millis();

}

void loop()
{
  long current_time = (long)millis();

  // run tcl at "frame rate"
  if((_picolTimer - current_time) <= 0)
  {  
    // runs a frame of picol.  If there is an error will
    // clear foreground script and run error script (flashing led) as background
    if(!PicolGlue.loop(_picoltime))
    {
       PicolGlue.set_foreground_script(NULL);
       PicolGlue.set_background_script(error_script); 
    }

    // blink the led.
    ledStatus_loop(_picoltime);

    // run the timer
    _picolTimer += _picoltime;
  }

  MQQ.Update();
}
