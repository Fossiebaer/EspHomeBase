// ConfigServer.h

#ifndef _CONFIGSERVER_h
#define _CONFIGSERVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include "FileAccess\FileAccess.h"
#include "EspHomeBase.h"

#define MAX_REPLACERS 10

typedef int (*replaceHandler)(char *buf);
typedef struct replaceEntry {
	char needle[12] = "";
	replaceHandler handler = nullptr;
};

class ConfigServer {
public:
	~ConfigServer();
	void start();
	static ConfigServer *getInstance();
	void handleClient();
	static ESP8266WebServer *server;
	bool addReplaceHandler(const char needle[], replaceHandler handler);
private:
	static replaceEntry replaceList[];
	static int replaceCount;
	ConfigServer();
	static void handleConfig();
	static void handleSet();
	static void handleFile();
	int replacer(char * buf, char * src);
	static ConfigServer *_instanz;
};

#define MAX_PAGE_SIZE 2200
extern char pageBuf[];

#endif
