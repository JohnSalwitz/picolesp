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
 
/* Set these to your desired credentials. */
static const char* ssid = "ASUS_2"; //ENTER YOUR WIFI SETTINGS
static const char* password = "HomeNet2006";

//#define SERVER_URL(_app) "http://192.168.1.121:5000/" _app
//#define SERVER_URL(_app) "http://192.168.1.205:5000/" _app
//#define SERVER_URL(_app) "http://raspberrypi:5000/" _app
//#define SERVER_URL(_app) "http://poseidon.local:5000/" _app

//static const char * _connect_url = SERVER_URL("connect");
//static const char * _log_url = SERVER_URL("post_log");
//static const char * _publish_url = SERVER_URL("publish");

static const char * _connect_path = "connect";
static const char * _log_path = "post_log";
static const char * _publish_path = "publish";

static const char * _mac_key = "mac";

static char *_serverURLS[] =
{
   "http://192.168.1.126:5000//",
   //"http://192.168.1.121:5000/",
   "http://192.168.1.205:5000/",
   NULL
};

static char *_logLevelnames[LogLevelType::count] =
{
  "error",
  "warning",
  "info",
  "debug"
};


static const int _serverMissMax = 10;

// Ram...
static char _buffer[1024];  
static char _buffer2[1024];

// Forward...
static void _ClearJSONBuffer();

networking::networking(void)
{
    m_isConnectedToNetwork = false;
    m_missedConnectionsToServer = 0;
    m_currentServerURL = _serverURLS;
}

networking::~networking(void)
{
}

//
// Advances the current server url so that the esp can pole multiple servers
// I would like to replace this with bonjor.  But until then I will just
// list out all possible urls.
//
char *networking::ChangeServer()
{
    m_currentServerURL += 1;
    if(*m_currentServerURL == NULL)
        m_currentServerURL = _serverURLS;
    return *m_currentServerURL;
}

//
// Returns url based on "current server" and path parameter
char *networking::GetServerUrl(char *buffer, const char *path)
{
    sprintf(buffer, "%s%s", *m_currentServerURL, path);
    return buffer;
}

//
// Begins connection to wifi network
//
bool networking::ConnectToNetwork()
{
    SerialPrint("ConnectToNetwork", "Connecting To:  ");
    SerialPrintLn("ConnectToNetwork", ssid);
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
        if (!m_isConnectedToNetwork) 
    		{
            SerialPrint("ConnectToMindControl", "Connected to:   ");
            SerialPrintLn("ConnectToMindControl",ssid);
            SerialPrint("ConnectToMindControl","IP address:  ");
            SerialPrintLn("ConnectToMindControl",WiFi.localIP().toString().c_str());
            m_isConnectedToNetwork = true;
            m_missedConnectionsToServer = 1;
        }

        // try to connect to server.  If fail then increase missed count. 
        // Missed count will eventually signal calling routine that connection to server is failing.
        if(GetServerCommand(networkEventHandler))
        {
              if(m_missedConnectionsToServer > 0)
              {
                m_missedConnectionsToServer = 0;
                sprintf(_buffer, "ReConnected To Server: %s", GetServerUrl(_buffer2, ""), m_missedConnectionsToServer);
                SerialPrintLn("networking::ConnectToMindControl", _buffer);
              }
        }
        else
        {
             m_missedConnectionsToServer += 1;    
             sprintf(_buffer, "Missed Connection To Server.  Server: %s Count: %d", GetServerUrl(_buffer2, ""), m_missedConnectionsToServer);
             SerialPrintLn("networking::ConnectToMindControl",_buffer);
             // switch servers... allows for multiple servers (until Bonjour works!) 
             ChangeServer();         
        }
        return (m_missedConnectionsToServer <= _serverMissMax);
    }
  	else
  	{
  		// handle reconnection here.
  		m_isConnectedToNetwork = false;
  	}
	  return m_isConnectedToNetwork;
}

// http://127.0.0.1:5000/connect?mac=<mac address>
bool networking::GetServerCommand(pNetworkEvent networkEventHandler)
{
    // form full get request (including mac address)
    char *url = GetServerUrl(_buffer2, _connect_path);
    sprintf(_buffer, "%s?%s=%s", url, _mac_key, WiFi.macAddress().c_str());
    
    // do get request...
    HTTPClient http;
    http.begin(_buffer);
    int httpCode = http.GET();
    if(httpCode != HTTP_CODE_OK)
    {
        sprintf(_buffer,"HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
        SerialPrintLn("GetServerCommand", _buffer);
        return false;
    }      

    // wait for and get return payload
    String payload = http.getString();
    if(payload.length() == 0)
    {
          http.end();
          return false;    
    }
    http.end(); 
    
    SerialPrintLn(payload.c_str());       
    // deserialize the json
    StaticJsonBuffer<1024> jsonBuffer2;
    JsonObject &root = jsonBuffer2.parseObject(payload.c_str());

    if(!root.success())
    {
        SerialPrintLn("GetServerCommand","ParseReturn Failed");
        return false;
    }      
     
    // handle any events/state changes in control message.
    for(JsonObject::iterator it=root.begin(); it!=root.end(); ++it)
    {
        SerialPrintLn("GetServerCommand", it->key);
         
        if (it->value.is<char*>())
        {  
            const char *value = it->value;
            if(*value != '\0')
            {
              networkEventHandler(it->key, value);

            }
            else
            {
              //SerialPrint("Skipped: ");
              //SerialPrintLn(it->key);
            }                                   
        }
        else
        {
            //SerialPrintLn("Not a String");
        }                      
    } 
        
    
    return true;
}

// Note "levelName" is restricted to whatever server defines as level names
bool networking::PostLog(const char *level, const char *message)
{
    HTTPClient http;
    char *url = GetServerUrl(_buffer2, _log_path);
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["levelname"] = level;
    root["message"] = message;  
    Post(url, root);
}

// Publishes a message to the server (other esps should subscribe to this)
bool networking::PostPublish(const char *message)
{
    HTTPClient http;
    char *url = GetServerUrl(_buffer2, _publish_path);
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["message"] = message;   
    Post(url, root);
}


// Note "levelName" is restricted to whatever server defines as level names
bool networking::PostLog(LogLevelType level, String message)
{
    PostLog(_logLevelnames[level], message.c_str());
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

// singleton..
networking NetworkHandler;
