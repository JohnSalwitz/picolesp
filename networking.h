#pragma once

typedef void (*pNetworkEvent)(const char*, const char*);

typedef enum e_logLevelType
{
  error,
  warning,
  info,
  debug,
  count
} LogLevelType;

// forward
#ifndef NETWORKING_CPP
class HTTPClient;
class JsonObject;
#endif

class networking
{
public:
	networking(void);
	~networking(void);

	bool        ConnectToNetwork();
	bool        ConnectToMindControl(pNetworkEvent networkEventHandler);

  bool        PostLog(const char *level, const char *message);
  bool        PostLog(LogLevelType level, String message);
  
  JsonObject  *Get(const char *url);
  bool        Post(const char *url, const char *message);
  bool        Post(const char *url, JsonObject& root);

private:
  JsonObject *ParseReturn(HTTPClient &http);
	bool        m_isConnected;
};

extern networking NetworkHandler;
