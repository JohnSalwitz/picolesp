#include <ArduinoJson.h>

#include "logger.h"
#include "debug2.h"
#include "cloud_mqqt.h"
#include "settings.h"

static char *_logLevelnames[LogLevelType::count] =
{
  "error",
  "warning",
  "info",
  "debug"
};

// Note "levelName" is restricted to whatever server defines as level names
bool logger_post(const char *level, const char *message)
{
    static char _buffer[1024];
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["client"] = ESP_NAME;
    root["time"] = logger_time();
    root["levelname"] = level;
    root["message"] = message;
    root.printTo(_buffer, sizeof(_buffer));
    MQQ.Publish(LOG_TOPIC, _buffer);
    return true;
}

// Note "levelName" is restricted to whatever server defines as level names
bool logger_post(LogLevelType level, const char *message)
{
    return logger_post(_logLevelnames[level], message);
}

static char *append_time(char *cp, int value, const char *singleForm, const char *pluralForm)
{
    const char *form = (value == 1) ? singleForm : pluralForm;
    return cp + sprintf(cp, form, value);
}

// prints long form of up-time (3 days, 5 hrs, 1 min, 0 sec)
const char *logger_uptime()
{
    static char _uptimeBuffer[256];
    static char *cp;
    long seconds = ((long)millis() + 500L) / 1000L;
    int days = (int)(seconds / (24L * 60L * 60L));
    seconds -= (long)(days * 24 * 60 * 60);
    int hours = (int)(seconds / (60L * 60L));
    seconds -= (long)(hours * 60 * 60);
    int minutes =  (int)(seconds / 60L);
    seconds -= (long)(minutes * 60);
  
    cp = append_time(_uptimeBuffer, days, "%d day, ", "%d days, ");
    cp = append_time(cp, hours, "%d hr, ", "%d hrs, ");
    cp = append_time(cp, minutes, "%d min, ", "%d mins, ");
    cp = append_time(cp, seconds, "%d sec", "%d secs");
         
    return _uptimeBuffer;
}

// prints short form of up-time (03:05:01:00)
const char *logger_time()
{
    static char _timeBuffer[128];
    long seconds = ((long)millis() + 500L) / 1000L;
    int days = (int)(seconds / (24L * 60L * 60L));
    seconds -= (long)(days * 24 * 60 * 60);
    int hours = (int)(seconds / (60L * 60L));
    seconds -= (long)(hours * 60 * 60);
    int minutes =  (int)(seconds / 60L);
    seconds -= (long)(minutes * 60);
  
    sprintf(_timeBuffer,"%02d:%02d:%02d:%02d",days, hours, minutes, seconds);
    return _timeBuffer;
}
