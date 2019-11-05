
#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include "debug2.h"
#include "picol_glue.h"
#include "networking.h"

const int _picolInterval = 1000 / 20;            // frames per seconds (in ms)
const int _networkInterval = 3 * 1000;           // network update rate (in ms)
const int _slowNetworkInterval = 90 * 1000;      // network update rate if server not responding (in ms)

static unsigned long _lastTime;
static long _picolTimer;
static long _networkTimer;
static char _name[64];

static void _handle_network_command(const char *command, const char *contents);

void setup()
{
  long current_time = (long)millis();
    
	Serial.begin(9600);
  //pinMode(2, OUTPUT);

  _lastTime = millis();
  
	SerialPrintLn("Setup");
  PicolGlue.setup();
	NetworkHandler.ConnectToNetwork();

  _networkTimer = current_time;
  _picolTimer = current_time;
}

void loop()
{
  long current_time = (long)millis();
  
  // run tcl at "frame rate"
  if((_picolTimer - current_time) <= 0)
  {  
    PicolGlue.loop(_picolInterval);
    _picolTimer += _picolInterval;
  }
   
  // check if any change in script...
  if((_networkTimer - current_time) <= 0)
  {
    // try to connect to server and get next command.  If this connection
    // is failing then slow down this attempt as it will bog down the esp8266.
    if(NetworkHandler.ConnectToMindControl(&_handle_network_command))
      _networkTimer += _networkInterval;
    else
      _networkTimer += _slowNetworkInterval;
      
  }
}

//
// Handles commands/events comming back from the server (from "connect")
//
static void _handle_network_command(const char *command, const char *contents)
{
  SerialPrint("Command: ");
  SerialPrintLn(command);
  SerialPrint("Contents: ");
  SerialPrintLn(contents);
  
  if(strstr(command, "background_script") != NULL)
  {
       PicolGlue.set_background_script(contents); 
       NetworkHandler.PostLog(LogLevelType::info, "Background Script Loaded From Server");   
       return;
  }

  if(strstr(command, "foreground_script") != NULL)
  {
       PicolGlue.set_foreground_script(contents); 
       NetworkHandler.PostLog(LogLevelType::info, "Foreground Script Loaded From Server");   
       return;
  }

  if(strstr(command, "name") != NULL)
  {
      strncpy(_name, contents, sizeof(_name));
      return;
  }
  
  SerialPrintLn("Ignored By Handler");
}
