//#include<stddef.h> 
#define NETWORKING_CPP

#include<string.h> 
#include <ArduinoJson.h>
#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h> 
#include <ESP8266HTTPClient.h>


#include "debug2.h"
#include "networking.h"

// Assuming singleton...
static ESP8266WiFiMulti _wifiMulti;
StaticJsonBuffer<1024> _jsonBuffer;
static char _buffer[1024];    



/* Set these to your desired credentials. */
static const char* ssid = "ASUS_2"; //ENTER YOUR WIFI SETTINGS
static const char* password = "HomeNet2006";

//#define SERVER_URL(_app) "http://poseidon.local:5000/" _app
#define SERVER_URL(_app) "http://192.168.1.121:5000/" _app
//#define SERVER_URL(_app) "http://192.168.1.205:5000/" _app
//define SERVER_URL(_app) "http://raspberrypi:5000/" _app
static const char * url = SERVER_URL("connect");
static const char * log_url = SERVER_URL("post_log");

//Web/Server address to read/write from
static const char* host = "192.168.1.205";

//static const char * url = "http://192.168.1.205:5000/connect";
//static const char * url = "http://192.168.1.121:5000/connect";
//static const char * log_url = "http://192.168.1.121:5000/post_log";

static char *_logLevelnames[LogLevelType::count] =
{
  "error",
  "warning",
  "info",
  "debug"
};


// Forward...
static void _ClearJSONBuffer();

networking::networking(void)
{
    m_isConnected = false;
}

networking::~networking(void)
{
}


//
// Begins connection to wifi network
//
bool networking::ConnectToNetwork()
{
    SerialPrintLn("ConnectToWIFI Startup");
    SerialPrint("Connecting To:  ");
    SerialPrintLn(ssid);
    _wifiMulti.addAP(ssid, password);
	  return true;
}

//
// Connects to esp control server.  Returns any change in background or foreground script
//
bool networking::ConnectToMindControl(pNetworkEvent networkEventHandler)
{
    // Wait for connection
    if (_wifiMulti.run() == WL_CONNECTED) 
    {
        if (!m_isConnected) 
    		{
            SerialPrint("Connected to:   ");
            SerialPrintLn(ssid);
            SerialPrint("IP address:  ");
            SerialPrintLn(WiFi.localIP().toString().c_str()); //IP address assigned to your ESP
            m_isConnected = true;
        }
        else 
        {
            JsonObject *root = Get(url);
            if(root)
            {      
                // handle any events/state changes in control message.
                for(JsonObject::iterator it=root->begin(); it!=root->end(); ++it)
                {
                    if (it->value.is<char*>())
                    {
                        const char *value = it->value;
                        if(*value != '\0')
                        {
                          networkEventHandler(it->key, value);
                        }
                        else
                        {
                          SerialPrint("Skipped: ");
                          SerialPrintLn(it->key);
                        }
                    }
                }       
            }
        }
    }
  	else
  	{
  		// handle reconnection here.
  		m_isConnected = false;
  	}
	  return m_isConnected;
}

// Note "levelName" is restricted to whatever server defines as level names
bool networking::PostLog(const char *level, const char *message)
{
    HTTPClient http;
    _ClearJSONBuffer();
    JsonObject& root = _jsonBuffer.createObject();
    root["levelname"] = level;
    root["message"] = message;
    Post(log_url, root);
}


// Note "levelName" is restricted to whatever server defines as level names
bool networking::PostLog(LogLevelType level, String message)
{
    PostLog(_logLevelnames[level], message.c_str());
}


JsonObject *networking::Get(const char *url)
{
    HTTPClient http;
    JsonObject *root = NULL;
    http.begin(url);
    int httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK)
    {
        root = ParseReturn(http);
    }
    else
    {
#ifdef DEBUG_MODE
      char buffer[256];
      sprintf(buffer,"HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
      SerialPrintLn(buffer); 
#endif    
    }  
    return root;
}

bool networking::Post(const char *url, const char *message)
{
      SerialPrintLn(message);
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "text/plain");
      http.POST(message);
      http.end();
}

bool networking::Post(const char *url, JsonObject& root)
{
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "application/json"); 
      root.printTo(_buffer, sizeof(_buffer));
      int httpCode = http.POST(_buffer);
      //String payload = http.getString();      
      //Serial.println(httpCode);   //Print HTTP return code
      //Serial.println(payload);    //Print request response payload
      http.end();  //Close connection 
}

// Deserialize a returned json document
JsonObject *networking::ParseReturn(HTTPClient &http)
{
    String payload = http.getString();
    JsonObject *root = NULL;
    if(payload.length() > 0)
    {
      SerialPrintLn(payload.c_str());
      _ClearJSONBuffer();
      root = &_jsonBuffer.parseObject(payload.c_str());
      if(!root->success())
      {
          root = NULL;
          SerialPrintLn("ParseReturn Failed"); 
      }
    }
    return root;
}

// Resets allocation in json buffer.  
// Caution... any references (roots) associated with this buffer will be dereferenced!
static void _ClearJSONBuffer()
{
  _jsonBuffer.clear();
}

// singleton..
networking NetworkHandler;
