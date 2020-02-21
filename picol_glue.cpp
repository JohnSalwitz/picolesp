#include <time.h>

#include "debug2.h"
#include "picol_glue.h"
#include "led_status.h"
#include "logger.h"
#include "settings.h"
#include "esp_relay.h"

#define PICOL_CONFIGURATION
#define PICOL_MAX_STR        256
#ifdef _MSC_VER
#    define PICOL_MAX_LEVEL  10
#else
#    define PICOL_MAX_LEVEL  30
#endif

#ifdef __MINGW32__
#    include <_mingw.h> /* For __MINGW64_VERSION_MAJOR. */
#endif

/* Optional features. Define as zero to disable. */
#define PICOL_FEATURE_ARRAYS    0
#if defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR)
/*                       ^^^ MinGW-w64 lacks glob.h. */
#    define PICOL_FEATURE_GLOB  0
#else
#    define PICOL_FEATURE_GLOB  0
#endif
#define PICOL_FEATURE_INTERP    0
#define PICOL_FEATURE_IO        0
#define PICOL_FEATURE_PUTS      1
#define PICOL_FEATUER_DEBUG      0
#define PICOL_FEATURE_TIMING    0
#define PICOL_REENTRANT         1


// Exit is used by picol...
void exit (int status);

// the interpreter...
#include "picol.h"

// tcl binding to Arduino functions
COMMAND(sleep);
COMMAND(sleepSec);
COMMAND(sleepMin);
COMMAND(setPinMode);
COMMAND(digitalWrite);
COMMAND(digitalRead);
#ifdef PICOL_LED_PIN
COMMAND(setLED);
#endif
#ifdef LED_STATUS
COMMAND(setLEDRate);
#endif
#ifdef PICOL_INPUT_PIN
COMMAND(readPin);
#endif
#if defined(PICOL_RELAY_SERIAL) || defined(PICOL_RELAY_PIN)
COMMAND(setRelay);
#endif

COMMAND(log);
COMMAND(publish);


void PicolGlueClass::setup(const char *defaultBackgroundScript)
{
    _interpreter = picolCreateInterp();
    _resetState();
 
    // used by tcl in idle mode
    picolSetIntVar(_interpreter, "idleTimer", 0);
  
    picolRegisterCmd(_interpreter, "sleep", picol_sleep, NULL);
    picolRegisterCmd(_interpreter, "sleepsec", picol_sleepSec, NULL);
    picolRegisterCmd(_interpreter, "sleepmin", picol_sleepMin, NULL);

    picolRegisterCmd(_interpreter, "pinmode", picol_setPinMode, NULL);
    picolRegisterCmd(_interpreter, "digitalwrite", picol_digitalWrite, NULL);
    picolRegisterCmd(_interpreter, "digitalread", picol_digitalRead, NULL);
    
#ifdef PICOL_LED_PIN
    picolRegisterCmd(_interpreter, "setled", picol_setLED, NULL);
#endif
#ifdef LED_STATUS
    picolRegisterCmd(_interpreter, "setledrate", picol_setLEDRate, NULL);
#endif
#ifdef PICOL_INPUT_PIN 
    picolRegisterCmd(_interpreter, "readpin", picol_readPin, NULL);
#endif 
#if defined(PICOL_RELAY_SERIAL) || defined(PICOL_RELAY_PIN)
    picolRegisterCmd(_interpreter, "setrelay", picol_setRelay, NULL);
#endif 

    picolRegisterCmd(_interpreter, "log", picol_log, NULL);
    picolRegisterCmd(_interpreter, "publish", picol_publish, NULL);

// esp/arduino constants
    picolSetIntVar(_interpreter, "HIGH", 0);
    picolSetIntVar(_interpreter, "LOW", 1);
    picolSetIntVar(_interpreter, "OUTPUT", OUTPUT);
    picolSetIntVar(_interpreter, "INPUT", INPUT);
      
#ifdef PICOL_INPUT_PIN
    picolSetIntVar(_interpreter, "inputpin", PICOL_INPUT_PIN);
    pinMode(PICOL_INPUT_PIN, INPUT);
#endif

#ifdef PICOL_LED_PIN
    picolSetIntVar(_interpreter, "ledpin", PICOL_LED_PIN);
    pinMode(PICOL_LED_PIN, OUTPUT);
#endif

#ifdef PICOL_RELAY_PIN
    picolSetIntVar(_interpreter, "relaypin", PICOL_RELAY_PIN);
    pinMode(PICOL_RELAY_PIN, OUTPUT);
#endif

    set_background_script(defaultBackgroundScript);
    set_foreground_script("");
    
    SerialPrintLn("Interpreter Setup Completed");
}

// returns if normal processing.  (False if an error)
bool PicolGlueClass::loop(int deltaTime)
{
   bool isOK = true;
    
  if(_sleepTime == 0)
  {
    char *script = (this->check_foreground_script()) ? (char *)_foregroundScript : (char *)_backgroundScript;
    int rc = picolEval2(_interpreter, script, _picolMode);

    // foreground script is one time only
    _foregroundScript[0] = '\0';
    
    // either ok -- standard return or yield... meaning that script will reenter.
    switch(rc)
    {
      case PICOL_OK:
         _picolMode = 1;
         break;
      case PICOL_YIELD:
         _picolMode = 2;                    // will reenter same script next iteration.
         break; 
      default:
         SerialPrintLn("PICOL ERROR!");
         logger_post("error", "Picol Error");   
         isOK = false;
         break;         
    }
  }
  else
  {
    _sleepTime = max(_sleepTime - deltaTime, 0);
  }
  
  picolSetIntVar(_interpreter, "idleTimer", 0);
  return isOK;
}

void PicolGlueClass::set_background_script(const char *newScript)
{
    if(newScript != NULL)
    {
      strncpy(_backgroundScript, newScript, sizeof(_backgroundScript));
      set_foreground_script("");   // Stop foreground (and reset state)  
    }
}

void PicolGlueClass::set_foreground_script(const char *newScript)
{
    if(newScript != NULL)
        strncpy(_foregroundScript, newScript, sizeof(_foregroundScript));
    else
       _foregroundScript[0] = '\0';
       
    // act on this change now.
   _resetState();
}

void PicolGlueClass::_resetState()
{
    _sleepTime = 0;
    _picolMode = 1;
}

void PicolGlueClass::p_delay(int milliSeconds)
{
  _sleepTime = (long)milliSeconds;
}

// sleep(milliseconds)
COMMAND(sleep)
{
  /* This is an example of how to wrap int functions. */
  int milliSeconds;
  ARITY2(argc == 2, "sleep");
  SCAN_INT(milliSeconds, argv[1]);
  PicolGlue.p_delay(milliSeconds);
  return PICOL_YIELD;
}

// sleepsec(seconds)
COMMAND(sleepSec)
{
  int seconds;
  ARITY2(argc == 2, "sleepsec");
  SCAN_INT(seconds, argv[1]);
  PicolGlue.p_delay(seconds * 1000);
  return PICOL_YIELD;
}

// sleepmin(minutes)
COMMAND(sleepMin)
{
  int minutes;
  ARITY2(argc == 2, "sleepmin");
  SCAN_INT(minutes, argv[1]);
  PicolGlue.p_delay(minutes * 1000 * 60);
  return PICOL_YIELD;
}

// digitalWrite(pin, state)
COMMAND(setPinMode)
{
  uint8_t pin;
  uint8_t pMode;
  ARITY2(argc == 3, "pinMode");
  SCAN_INT(pin, argv[1]);
  SCAN_INT(pMode, argv[2]);
  pinMode(pin, pMode);
  return PICOL_OK;
}

// digitalWrite(pin, state)
COMMAND(digitalWrite)
{
  uint8_t pin;
  uint8_t state;
  ARITY2(argc == 3, "digitalwrite");
  SCAN_INT(pin, argv[1]);
  SCAN_INT(state, argv[2]);
  digitalWrite(pin, state);
  return PICOL_OK;
}

// digitalRead(pin)
COMMAND(digitalRead)
{
  uint8_t pin;
  ARITY2(argc == 2, "digitalread");
  SCAN_INT(pin, argv[1]);
  return picolSetIntResult(interp, digitalRead(pin));
}

#ifdef PICOL_LED_PIN
// setLED(state)
COMMAND(setLED)
{
  uint8_t state;
  ARITY2(argc == 2, "setLED");
  SCAN_INT(state, argv[1]);
  if(state == 0)
      digitalWrite(PICOL_LED_PIN, HIGH); 
  else
      digitalWrite(PICOL_LED_PIN, LOW); 
  return PICOL_OK;
}
#endif

#ifdef LED_STATUS
// setLEDRate(state)
COMMAND(setLEDRate)
{
  uint8_t rate;
  ARITY2(argc == 2, "setLEDRate");
  SCAN_INT(rate, argv[1]);
  ledStatus_setRate(rate);
  return PICOL_OK;
}
#endif

#ifdef PICOL_INPUT_PIN
// readPin()
COMMAND(readPin)
{
  ARITY2(argc == 1, "readPin");
  int i = digitalRead(PICOL_INPUT_PIN);
  Serial.println(i);
  return picolSetIntResult(interp, i);  
}
#endif


#ifdef PICOL_RELAY_SERIAL
// setRelay(state)
COMMAND(setRelay)
{
  uint8_t state;
  ARITY2(argc == 2, "setRelay");
  SCAN_INT(state, argv[1]);
  espRelay_setState(state);
  return PICOL_OK;
}
#endif

#ifdef PICOL_RELAY_PIN
// setRelay(state)
COMMAND(setRelay)
{
  uint8_t state;
  ARITY2(argc == 2, "setRelay");
  SCAN_INT(state, argv[1]);
  if(state == 0)
      digitalWrite(PICOL_RELAY_PIN, LOW); 
  else
      digitalWrite(PICOL_RELAY_PIN, HIGH); 
  return PICOL_OK;
}
#endif


// to do...protect buffers!
// log(level, message)
COMMAND(log)
{
    ARITY2(argc == 3, "log level msg");
    logger_post(argv[1], argv[2]);
    return PICOL_OK;
}

// Publish a message to the server (triggered by something...)
COMMAND(publish)
{
    ARITY2(argc == 2, "publish msg");
    //NetworkHandler.PostPublish(argv[1]);
    return PICOL_OK;
}


/*
 * Functions not (yet) handled by esp that picol references...
 */
void exit (int status)
{
  while(1) {}
}

// Singleton
PicolGlueClass PicolGlue;
