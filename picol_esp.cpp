#include <Arduino.h>
#include <time.h>

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
#define PICOL_FEATURE_TIMING	0


#include "picol.h"

// typedef int (*picol_Func)(struct picolInterp *interp, int argc, char **argv, void *pd);

static picolInterp *_interp = NULL;

// tcl binding to Arduino functions
COMMAND(sleep);
COMMAND(sleepSec);
COMMAND(sleepMin);
COMMAND(digitalWrite);
COMMAND(digitalRead);


void setup()
{
	_interp = picolCreateInterp();

	picolSetIntVar(_interp, "relaypin", 2);
	picolSetIntVar(_interp, "HIGH", 1);
	picolSetIntVar(_interp, "LOW", 0);

	// used by tcl in idle mode
	picolSetIntVar(_interp, "idleTimer", 0);

    picolRegisterCmd(_interp, "sleep", picol_sleep, NULL);
    picolRegisterCmd(_interp, "sleepsec", picol_sleepSec, NULL);
    picolRegisterCmd(_interp, "sleepmin", picol_sleepMin, NULL);

    picolRegisterCmd(_interp, "digitalwrite", picol_digitalWrite, NULL);
    picolRegisterCmd(_interp, "digitalread", picol_digitalRead, NULL);

}

static char *_picolIdleScript = NULL;
static char *_picolActiveScript = NULL;

void loop()
{
	// check message and then when get one...
	if(0)
	{
		_picolActiveScript = "puts {Hello, Active!}";
	}

	if(0)
	{
		_picolIdleScript = "puts {Hello, Idle!}";
	}

	char *pico_text = "puts {Hello, World!}";

	if(_picolActiveScript)
	{

		int rc = picolEval(_interp, _picolActiveScript);
		if (rc != PICOL_OK)
		{
			// error
		}
		_picolActiveScript = NULL;
		picolSetIntVar(_interp, "idleTimer", 0);
	}

	if(_picolIdleScript)
	{
		int rc = picolEval(_interp, _picolIdleScript);
		if (rc != PICOL_OK)
		{
			// error
		}
	}
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
 *
 *
 */
