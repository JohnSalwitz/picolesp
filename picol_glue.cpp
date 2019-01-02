#include <time.h>

#include "debug2.h"
#include "picol_glue.h"
#include "networking.h"

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
#define PICOL_FEATUER_DEBUG		  0
#define PICOL_FEATURE_TIMING	  0
#define PICOL_REENTRANT         1

// Exit is used by picol...
void exit (int status);

// the interpreter...
#include "picol.h"

// typedef int (*picol_Func)(struct picolInterp *interp, int argc, char **argv, void *pd);


// tcl binding to Arduino functions
COMMAND(sleep);
COMMAND(sleepSec);
COMMAND(sleepMin);
COMMAND(digitalWrite);
COMMAND(digitalRead);
COMMAND(log);


void PicolGlueClass::setup()
{
  	_interpreter = picolCreateInterp();
    _resetState();
    
  	picolSetIntVar(_interpreter, "relaypin", 2);
  	picolSetIntVar(_interpreter, "HIGH", 1);
  	picolSetIntVar(_interpreter, "LOW", 0);
  
  	// used by tcl in idle mode
  	picolSetIntVar(_interpreter, "idleTimer", 0);
  
    picolRegisterCmd(_interpreter, "sleep", picol_sleep, NULL);
    picolRegisterCmd(_interpreter, "sleepsec", picol_sleepSec, NULL);
    picolRegisterCmd(_interpreter, "sleepmin", picol_sleepMin, NULL);
  
    picolRegisterCmd(_interpreter, "digitalwrite", picol_digitalWrite, NULL);
    picolRegisterCmd(_interpreter, "digitalread", picol_digitalRead, NULL);

    picolRegisterCmd(_interpreter, "log", picol_log, NULL);
    
    set_background_script("digitalwrite 2 1\nsleepsec 1\ndigitalwrite 2 0\nsleepsec 1\n");
    set_foreground_script("");
    
  	SerialPrintLn("interp Setup Completed");
}

void PicolGlueClass::loop(int deltaTime)
{
  if(_sleepTime == 0)
  {
    char *script = (*_foregroundScript != '\0') ? (char *)_foregroundScript : (char *)_backgroundScript;
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
         NetworkHandler.PostLog("error", "Picol Error");    
         break;         
    }
  }
  else
  {
    _sleepTime = max(_sleepTime - deltaTime, 0);
  }
  
  picolSetIntVar(_interpreter, "idleTimer", 0);
}

void PicolGlueClass::set_background_script(const char *newScript)
{
    strncpy(_backgroundScript, newScript, sizeof(_backgroundScript));
    set_foreground_script("");       // override foreground (and reset state)
}

void PicolGlueClass::set_foreground_script(const char *newScript)
{
    strncpy(_foregroundScript, newScript, sizeof(_foregroundScript));
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

// digitalWrite(pin, state)
COMMAND(digitalRead)
{
	uint8_t pin;
	uint8_t state;
	ARITY2(argc == 2, "digitalread");
	SCAN_INT(pin, argv[1]);
  return picolSetIntResult(interp, digitalRead(pin));
}

// to do...protect buffers!
// log(level, message)
COMMAND(log)
{
    ARITY2(argc == 3, "log level msg");
    NetworkHandler.PostLog(argv[1], argv[2]);
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
