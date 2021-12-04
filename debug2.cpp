#include "debug2.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h
#endif

#ifdef DEBUG_MODE
void SerialPrint(const char *functionName, const char *str)
{
    Serial.print(functionName);
    Serial.print(" -- ");
    Serial.print(str); 
    Serial.flush();  
}

void SerialPrintLn(const char *functionName, const char *str)
{
    Serial.print(functionName);
    Serial.print(" -- ");
    Serial.println(str);
    Serial.flush();  
}
#else
void SerialPrint(const char *functionName, const char *str)
{
}

void SerialPrintLn(const char *functionName, const char *str)
{
}
#endif
