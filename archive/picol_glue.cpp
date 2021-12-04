#include <Arduino.h>
#include <time.h>
#include "debug2.h"
#include "picol_glue.h"

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
#define PICOL_FEATUER_DEBUG		0
#define PICOL_FEATURE_TIMING	0

//
//  Forward Instance/Glue/Binding between picol and C++
//

void set_background_script(const char *newScript);
void set_foreground_script(const char *newScript);

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

void PicolGlueClass::setup()
{
	picolInterp *_interpreter = picolCreateInterp();

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

	_activeScript = "puts {Hello, Idle And Wait}\nsleepsec 5";

	SerialPrintLn("PicolGlueClass::setup", "interp Setup Completed");
}

void PicolGlueClass::loop()
{
	int rc = picolEval(_interpreter, (char *)_activeScript);
	if (rc != PICOL_OK)
	{
		SerialPrintLn("PicolGlueClass::loop","PICOL ERROR!");
	}
	picolSetIntVar(_interpreter, "idleTimer", 0);
}


// sleep(milliseconds)
COMMAND(sleep)
{
	/* This is an example of how to wrap int functions. */
	int milliSeconds;
	ARITY2(argc == 2, "sleep");
	SCAN_INT(milliSeconds, argv[1]);
	delay(milliSeconds);
	return PICOL_OK;
}

// sleepsec(seconds)
COMMAND(sleepSec)
{
	int seconds;
	ARITY2(argc == 2, "sleepsec");
	SCAN_INT(seconds, argv[1]);
	delay(seconds * 1000);
	return PICOL_OK;
}

// sleepmin(minutes)
COMMAND(sleepMin)
{
	int minutes;
	ARITY2(argc == 2, "sleepmin");
	SCAN_INT(minutes, argv[1]);
	delay(minutes * 1000 * 60);
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

// digitalWrite(pin, state)
COMMAND(digitalRead)
{
	uint8_t pin;
	uint8_t state;
	ARITY2(argc == 2, "digitalread");
	SCAN_INT(pin, argv[1]);
    return picolSetIntResult(interp, digitalRead(pin));
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