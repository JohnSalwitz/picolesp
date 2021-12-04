
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
#include "clock_timer.h"

#define PICOL_TIME 1000         // ms between frames

void setup()
{
  const char *backgroundScript;

#ifdef ESP32 
  Serial.begin(115200);
#else
  Serial.begin(9600);
#endif
  
  SerialPrintLn("setup", "MQQ Init...");

  MQQ.Init(ESP_NAME);
  logger_post(LogLevelType::info, "Connected"); 

  SerialPrintLn("setup","Clock Timer...");
  clockTimer_Init();
  
  SerialPrintLn("setup","SubscriptionsInit...");
  SubscriptionsInit();

  // led blinker...
  SerialPrintLn("setup","ledStatus_setup...");
  ledStatus_setup(); 

  SerialPrintLn("setup","StaticStorage_Init...");
  StaticStorage_Init(default_backgroundScript);
  backgroundScript = StaticStorage_Read();

  SerialPrintLn("setup","Setup Picol With Default Script: ");
  SerialPrintLn("","-------------------------------------");
  SerialPrintLn("",backgroundScript);
  SerialPrintLn("","-------------------------------------");
  PicolGlue.setup(backgroundScript);

}

void loop()
{
    // runs a frame of picol.  If there is an error will
    // clear foreground script and run error script (flashing led) as background
    if(!PicolGlue.loop(PICOL_TIME))
    {
       PicolGlue.set_foreground_script(NULL);
       PicolGlue.set_background_script(error_script); 
    }

    // update the clock
    clockTimer_Update();
     
    // blink the led.
    ledStatus_loop(PICOL_TIME);

    // check for messages
    MQQ.Update();

    // does this put the esp to sleep?
    delay(PICOL_TIME);
}
