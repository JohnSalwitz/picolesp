#include "StateMachine.h"
#include "States.h"
#include "Morse.h"
#include "Debug.h"
#include "Ticker.h"

const long _forgroundInteval = 1000 / 60;            // frame update rate (for foreground)
const long _updateInterval = 1000;                   // frame uprate interval (for background)

// seporate thread for led update...
static Ticker morseTicker;

// forward
void  morseUpdate();

//=======================================================================
//                    Power on Set Up
//=======================================================================
void setup() 
{
  Serial.begin(9600);

  // 2nd thread for led update as main thread is blocking (http)
  morseTicker.attach_ms(_forgroundInteval, morseUpdate);  
  Morse.Transmit("____    ");
  
  StateClass *firstState = GetState("ConnectToWIFI");
	StateMachine.Start(firstState);
}

    
//=======================================================================
//                    Main Update
//=======================================================================
void loop()
{
    StateMachine.Update((int)_updateInterval);
    delay(_updateInterval);
}

//=======================================================================
//                   Led Update (morse)
//=======================================================================
void morseUpdate()
{
    Morse.Update((int)_forgroundInteval);
}
