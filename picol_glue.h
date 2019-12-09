
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
	void setup(const char *defaultBackgroundScript);
	bool loop(int deltaTime);
  void p_delay(int milliSeconds);
  
  void set_background_script(const char *newScript);
  void set_foreground_script(const char *newScript);
  bool check_foreground_script() {return _foregroundScript[0] != '\0';}   // returns true if foreground script is running
  
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
