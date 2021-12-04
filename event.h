//
// Created by johnsalwitz on 11/18/21.
//

#ifndef _EVENT_H
#define _EVENT_H

#define ACTION_LIMIT 4              // max # actions per event
#define EVENT_LIMIT 8               // max # of events

typedef enum e_action_type
{
    SET_PIN_HIGH,
    SET_PIN_LOW,
    SET_LED_ON,
    SET_LED_OFF,
    SEND_LOG,
    count
} EventActionType;


// the act of an event
typedef struct EventAction {
    int  id;                                // unique identifier
    EventActionType type;
    char parameter[256];
    int repeat_time;                        // in seconds (0 means no repeat)
    int repeat_limit;                       // limit to repetitions (0 means no limit)
};

//
typedef struct EventRecord {
    char name[32];
    char trigger_message[64];               // the message that triggers this
    EventAction actions[];
};

#endif //_EVENT_H
