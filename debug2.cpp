#include "debug2.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h
#endif

#ifdef DEBUG_MODE
void SerialPrint(const char *str)
{
    Serial.print(str); 
    Serial.flush();  
}

void SerialPrintLn(const char *str)
{
    Serial.println(str);
    Serial.flush();  
}
#else
void SerialPrint(const char *)
{
}

void SerialPrintLn(const char *)
{
}
#endif
