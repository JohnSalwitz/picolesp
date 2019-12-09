
#ifndef LED_STATUS
#define LED_STATUS

#define LED_STATUS_PIN 1
//
// Led Flasher.
//
void ledStatus_setup();
void ledStatus_setRate(int beatsPerMinute);
void ledStatus_loop(int deltaTime);

#endif
