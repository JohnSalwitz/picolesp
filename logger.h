#ifndef _LOGGER_H
#define _LOGGER_H
 
#define LOG_TOPIC "esp/log"

 // minimum log level to be transmitted
#define LOG_LEVEL_CHECK(log_level) ((log_level) >= LogLevelType::info)  
   
    
typedef enum e_logLevelType
{
  debug,
  info,
  warning,
  error,
  count
} LogLevelType;



// Note "levelName" is restricted to whatever server defines as level names
bool logger_post(const char *level, const char *message);
bool logger_post(LogLevelType level, const char *message);
//const char *logger_uptime();
//const char *logger_time();

#endif
