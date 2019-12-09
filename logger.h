#ifndef _LOGGER_H
#define _LOGGER_H
 
#define LOG_TOPIC "esp/log"

typedef enum e_logLevelType
{
  error,
  warning,
  info,
  debug,
  count
} LogLevelType;


// Note "levelName" is restricted to whatever server defines as level names
bool logger_post(const char *level, const char *message);
bool logger_post(LogLevelType level, const char *message);
const char *logger_uptime();
const char *logger_time();

#endif
