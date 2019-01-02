
#ifndef _PICOLGLUE_H
#define _PICOLGLUE_H

class picolInterp;

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class PicolGlueClass
{

public:
	void setup();
	void loop(int deltaTime);
  
  void set_background_script(const char *newScript);
  void set_foreground_script(const char *newScript);
  void p_delay(int milliSeconds);

private:
  void    _resetState();
 
	picolInterp		*_interpreter;
  char   _backgroundScript[512];
  char   _foregroundScript[1024];
  int    _sleepTime;
  int    _picolMode;
};

extern PicolGlueClass PicolGlue;

#endif
