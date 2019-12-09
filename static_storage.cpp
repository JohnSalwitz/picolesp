
#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include <ESP_EEPROM.h> 
#include "version.h"
#include "debug2.h"
#include "logger.h"
#include "static_storage.h"

#define EEROM_SIZE (1024)     // gross size of storage
#define EEROM_TRIES (2)       // # of tries to read/write EEROM

static struct EEPromHeader {
  long    versionNumber;
} _EEPromHeader;

static char _payload[EEROM_SIZE-sizeof(_EEPromHeader)];

// Reads from eerom.  If version # mismatch will use default payload and write eerom.
bool StaticStorage_Init(const char *defaultPayload)
{
  SerialPrintLn("INIT");
  
  // needed?
  memset(&_EEPromHeader,0,sizeof(EEPromHeader));
  memset(&_payload,0,sizeof(_payload));
  
  EEPROM.begin(EEROM_SIZE);

      SerialPrintLn("BEGIN");
  // The begin() call is required to initialise the EEPROM library
  for(int i = 0;i < EEROM_TRIES;i++)
  {
      char buf[128];
        SerialPrintLn("TRY");
      EEPROM.get(0, _EEPromHeader);
      sprintf(buf, "Read Version from EEPROM: %d",_EEPromHeader.versionNumber);
      SerialPrintLn(buf);
      logger_post(LogLevelType::info, buf);  
      
      // Check version match.  Otherwise... will init.
      if(_EEPromHeader.versionNumber == BUILD_VERSION_CODE)
      {
          if(i == 0)
              logger_post(LogLevelType::info, "EEPROM Version Matched.  Using Saved Version");  
          return true;
      }

      SerialPrintLn("EEPROM Version Did Not Match... ReWriting ");    
      logger_post(LogLevelType::info, "EEPROM Version Did Not Match... ReWriting ");    
      _EEPromHeader.versionNumber = BUILD_VERSION_CODE;
      StaticStorage_Write(defaultPayload);
  }
  return false;
}

bool StaticStorage_Write(const char *payLoad)
{      
    // Write the header...
    EEPROM.put(0, _EEPromHeader);

    // Write the payload...
    const uint8_t *cp = (const uint8_t *)payLoad;
    int length = 0;
  
    for(int offset = sizeof(_EEPromHeader);offset < EEROM_SIZE;offset++,cp++)
    {
        EEPROM.write(offset, *cp);
        length += 1;
        if(*cp == '\0') break;
    }
  
    bool ok = EEPROM.commit();
    if(!ok)
    {
        SerialPrintLn("EEROM Commit failed");
    }
    else
    {
      char buf[128];
      sprintf(buf, "Successful EEROM Write Payload Length (Bytes): %d",length);
      SerialPrintLn(buf);
      logger_post(LogLevelType::info, buf);   
    }
  
    return ok;
}

const char *StaticStorage_Read()
{
    uint8_t *cp = (uint8_t *)_payload;
    for(int offset = sizeof(_EEPromHeader);offset < EEROM_SIZE;offset++,cp++)
    {
        *cp = EEPROM.read(offset);
        if(*cp == '\0') break;
    }  
    return _payload;
}
