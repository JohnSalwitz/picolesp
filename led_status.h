
#ifndef LED_STATUS
#define LED_STATUS

#ifdef ESP32 
#define LED_STATUS_PIN   14
#else
#define LED_STATUS_PIN   1
#endif

//
// Led Flasher.
//
void ledStatus_setup();
void ledStatus_setRate(int beatsPerMinute);
void ledStatus_loop(int deltaTime);

#endif
