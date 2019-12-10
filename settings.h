#ifndef _SETTINGS_H
#define _SETTINGS_H

//
// Default (background) scripts for different esp roles.
// This module necessary because I have not gotten the esp to be able to flash it's own memory so I can't load this at runtime
// to do:  fix this
//

#define CAT_FAN
//#define CAT_SENSOR
//#define TESTER

#ifdef TESTER
#define ESP_NAME "tester"
//-------------------------------------------------------------------------
static const char *default_backgroundScript =
    "setled 1\n"
    "sleepsec 1\n"
    "setled 0\n"  
    "sleepsec 1\n";
    
//#define PICOL_LED_PIN   1
//#define PICOL_INPUT_PIN 1
//#define PICOL_RELAY
//--------------------------------------------------------------------------
#endif

#ifdef CAT_FAN
#define ESP_NAME  "cat_fan"
//-------------------------------------------------------------------------
static const char *default_backgroundScript =
    "log info \"Start Cat Fan Cycle\"\n"
    "setledrate 60\n"
    "setrelay 0\n"
    "sleepmin 22\n"
    "setrelay 1\n"
    "setledrate 240\n"
    "sleepmin 8\n";

static const char *cat_detected_script =
    "log info \"Fan is turning on for the cat\"\n"
    "setrelay 1\n"
    "setledrate 240\n"
    "sleepmin 10\n"
    "setrelay 0\n";
    
//#define PICOL_LED_PIN   1
//#define PICOL_INPUT_PIN 1
#define PICOL_RELAY
//--------------------------------------------------------------------------
#endif

#ifdef CAT_SENSOR
#define ESP_NAME "cat_sensor"
//-------------------------------------------------------------------------
static const char *default_backgroundScript =
    "set pinval [digitalread 1]\n"
    "if {$pinval == 1} {\n"
    "    publish cat_in_box\n"
    "}\n"
    "sleepsec 10\n";
    
//#define PICOL_LED_PIN   2
#define PICOL_INPUT_PIN 1
//#define PICOL_RELAY
//--------------------------------------------------------------------------
#endif


// Fast blinking led means there was an error
static const char *error_script =
    "setledrate 600\n"
    "sleepsec 10\n";

#endif
