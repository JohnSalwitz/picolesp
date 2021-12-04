#include <ArduinoJson.h>

#include "logger.h"
#include "debug2.h"
#include "cloud_mqqt.h"
#include "settings.h"
#include "clock_timer.h"

static char *_logLevelnames[LogLevelType::count] =
{
  "debug",
  "info",
  "warning",
  "error"
};

// Note "levelName" is restricted to whatever server defines as level names
bool logger_post(const char *level, const char *message)
{
    DynamicJsonDocument root(1024);
    static char _buffer[1024];

    root["client"] = ESP_NAME;
    root["time"] = clockTimer_FormatTime(_buffer);
    root["levelname"] = level;
    root["message"] = message;
    serializeJson(root, _buffer);

    MQQ.Publish(LOG_TOPIC, _buffer);

    return true;
}

// Note "levelName" is restricted to whatever server defines as level names
bool logger_post(LogLevelType level, const char *message)
{
    if(LOG_LEVEL_CHECK(level))
    {
          return logger_post(_logLevelnames[level], message);
    }

    return true;
}

static char *append_time(char *cp, int value, const char *singleForm, const char *pluralForm)
{
    const char *form = (value == 1) ? singleForm : pluralForm;
    return cp + sprintf(cp, form, value);
}
