//
// Created by johnsalwitz on 11/15/21.
//
#ifdef ESP32 
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <NTPClient.h>
#include "clock_timer.h"
#include "debug2.h"

// delta from local (pst) and udp
#define PST_OFFSET_IN_SECONDS (-8 * 60 * 60)
// how often it reaches out to ntp (ie: once a day)
#define UPDATE_INTERVAL_MS (24 * 60 * 60 * 1000)

#define HOURS(epoch) ((epoch  % 86400L) / 3600)
#define MINUTES(epoch) ((epoch % 3600) / 60)
#define SECONDS(epoch) (epoch % 60)

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP, "pool.ntp.org", PST_OFFSET_IN_SECONDS, UPDATE_INTERVAL_MS);
static unsigned long _startupTime = 0;

// forward
static void _getFormattedTime(unsigned long epochTime, char *buffer);

void clockTimer_Init()
{
    SerialPrintLn("ClockTimer::Init", "Connecting To pool.ntp.org");
    timeClient.begin();
}

void clockTimer_Update() 
{
  timeClient.update();
  if(timeClient.isTimeSet()) 
  {
    if(_startupTime == 0)
    {
       char buffer[256];
       SerialPrintLn("StartupTime", clockTimer_FormatTime(buffer));
      _startupTime = timeClient.getEpochTime();
    }
  }
}

// returns time
unsigned long clockTimer_GetTime()
{
  return timeClient.getEpochTime();
}

// prints short form of time (03:05:01:00)
char *clockTimer_FormatTime(char *buffer)
{
    unsigned long epochTime = clockTimer_GetTime();
    sprintf(buffer,"%02d:%02d:%02d", HOURS(epochTime), MINUTES(epochTime), SECONDS(epochTime));
    return buffer;
}

// returns up time
unsigned long clockTimer_GetUpTime()
{
  return timeClient.getEpochTime() - _startupTime;
}

// prints long form of time (as in duration) (05:01:00)
char *clockTimer_FormatUpTime(char *buffer)
{
    int seconds = clockTimer_GetUpTime();
    int days = (int)(seconds / (24L * 60L * 60L));
    seconds -= (long)(days * 24 * 60 * 60);
    int hours = (int)(seconds / (60L * 60L));
    seconds -= (long)(hours * 60 * 60);
    int minutes =  (int)(seconds / 60L);
    seconds -= (long)(minutes * 60);
    sprintf(buffer,"%d days %d hours %d mins %d secs", days, hours, minutes, seconds);
    return buffer;
}
