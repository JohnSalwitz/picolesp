#include "debug2.h"
#include "picol_glue.h"
#include "cloud_mqqt.h"
#include "static_storage.h"
#include "logger.h"
#include "settings.h"
#include "subscriptions.h"


static void _handleReset(const char *contents)
{ 
   PicolGlue.set_foreground_script(NULL);
   PicolGlue.set_background_script(default_backgroundScript); 
   // Replace default power script.
   StaticStorage_Write(default_backgroundScript);
}

static void _handlePing(const char *contents)
{ 
  char buffer[256];
  sprintf(buffer, "Up: %s", logger_uptime());
  SerialPrintLn(buffer);
  logger_post(LogLevelType::info, buffer); 
}

static void _handleSetForeground(const char *contents)
{
   PicolGlue.set_foreground_script(contents); 
}

static void _handleSetBackground(const char *contents)
{
   PicolGlue.set_background_script(contents); 
   // Replace default power script.
   StaticStorage_Write(contents);  
}

#ifdef CAT_FAN
static void _handleCatFanRun(const char *)
{
   if(!PicolGlue.check_foreground_script())
        PicolGlue.set_foreground_script(cat_detected_script); 
   else
        logger_post(LogLevelType::info, "Cat Script Already Running");   
   return;
}
#endif

#include <functional>
#define SUBSCRIPTION_HANDLER std::function<void(const char *contents)>

struct SubscriptionDef
{
  const char              *topic;
  SUBSCRIPTION_HANDLER    handler;
};


#define GENERIC_TOPIC(topic) "esp/" topic
#define NAMED_TOPIC(topic) GENERIC_TOPIC(ESP_NAME "/" topic)

// binds topics to topic handlers...
SubscriptionDef _Subscriptions[] = 
{
  {NAMED_TOPIC("reset"), _handleReset},
  {GENERIC_TOPIC("reset_all"), _handleReset},
  {NAMED_TOPIC("ping"), _handlePing},
  {GENERIC_TOPIC("ping_all"), _handlePing},
  {NAMED_TOPIC("foreground_script"), _handleSetForeground},  
  {NAMED_TOPIC("background_script"), _handleSetBackground},
#ifdef CAT_FAN
  {GENERIC_TOPIC("cat_detected"), _handleCatFanRun},
#endif
  {NULL, NULL}
};


//
// Handles subscribed messages coming from MQQT
//
static void _SubscriptionsCallback(char* topic, uint8_t* payload, unsigned int length) 
{
  char topic_buffer[128];
  char contents[1024];
   
  strncpy(topic_buffer, topic, sizeof(topic_buffer));
  
  memcpy(contents, payload, length);
  contents[length] = '\0'; 
  
  for(SubscriptionDef *subscription = _Subscriptions; subscription->topic != NULL; subscription += 1)
  {  
    if(strstr(topic_buffer, subscription->topic) != NULL)
    {  
        char buffer[128];               
        SerialPrint("Contents: ");
        SerialPrintLn(contents);     
        sprintf(buffer, "Client Handling Topic: %s", subscription->topic);
        SerialPrintLn(buffer);
        logger_post(LogLevelType::info, buffer);   
        subscription->handler(contents);
        return;
    }
  }

  logger_post(LogLevelType::info, "Ignored Command");   
  SerialPrintLn("Command Ignored By ESPP Handler");
}

// informs mqqt broker of the subscriptions needed based on above list.
void SubscriptionsInit() 
{
  for(SubscriptionDef *subscription = _Subscriptions; subscription->topic != NULL; subscription += 1)
  {
      SerialPrint("Subscribe To: ");
      SerialPrintLn(subscription->topic);
      MQQ.Subscribe(subscription->topic);
      delay(100);
  }
  MQQ.SetCallback(_SubscriptionsCallback);
}
