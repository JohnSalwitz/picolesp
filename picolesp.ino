
#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include "debug2.h"
#include "picol_glue.h"
#include "networking.h"

const int _picolInterval = 1000 / 20;             // frames per seconds (in ms)
const int _networkInterval = 2000;               // network update per second (in ms)

static unsigned long _lastTime;
static long _picolTimer = 0;
static long _networkTimer = 0;
static char _name[64];

static void _handle_network_command(const char *command, const char *contents);

void setup()
{
	Serial.begin(9600);
  pinMode(2, OUTPUT);

  _lastTime = millis();
  
	SerialPrintLn("Setup");
  PicolGlue.setup();
	NetworkHandler.ConnectToNetwork();
}

void loop()
{
  long time = (long)millis();
  long deltaTime = time - _lastTime;
  _lastTime = time;

  _picolTimer -= deltaTime;
  _networkTimer -= deltaTime;
  
  // run tcl at "frame rate"
  if(_picolTimer <= 0)
  {  
    PicolGlue.loop(_picolInterval);
    _picolTimer += _picolInterval;
  }
   
  // check if any change in script...
  if(_networkTimer <= 0)
  {
	  NetworkHandler.ConnectToMindControl(&_handle_network_command);
    _networkTimer += _networkInterval;
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
       NetworkHandler.PostLog(LogLevelType::info, "Name Changed By Server");   
       return;
  }
  
  SerialPrintLn("Ignored By Handler");
}
