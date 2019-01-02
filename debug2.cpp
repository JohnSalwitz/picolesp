// 
// 
// 

#include "debug2.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

void SerialPrint(const char *str)
{
    str = str;
#ifdef DEBUG_MODE
    Serial.print(str); 
#endif
}

void SerialPrintLn(const char *str)
{
    str = str;
#ifdef DEBUG_MODE
    Serial.println(str);
#endif
}
