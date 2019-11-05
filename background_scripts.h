
//
// Default (background) scripts for different esp roles.
// This module necessary because I have not gotten the esp to be able to flash it's own memory so I can't load this at runtime
// to do:  fix this
//

//#define CAT_FAN
//#define CAT_SENSOR
#define TESTER

#ifdef TESTER
//-------------------------------------------------------------------------
static const char *default_backgroundScript =
    "setled 1\n"
    "sleepsec 1\n"
    "setled 0\n"
    "sleepsec 1\n";
    
#define PICOL_LED_PIN   2
//#define PICOL_INPUT_PIN 1
#define PICOL_RELAY
//--------------------------------------------------------------------------
#endif

#ifdef CAT_FAN
//-------------------------------------------------------------------------
static const char *default_backgroundScript =
    "log info \"Start Cat Fan Cycle\"\n"
    "setrelay 1\n"
    "setled 1\n"
    "sleepmin 8\n"
    "setrelay 0\n"
    "setled 0\n"
    "sleepmin 22\n";


#define PICOL_LED_PIN   2
//#define PICOL_INPUT_PIN 1
#define PICOL_RELAY
//--------------------------------------------------------------------------
#endif

#ifdef CAT_SENSOR
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
