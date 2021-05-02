//PAGE & APIS -----------------------------------------
void handleSensorPage();
void handleGetState();
void handleLedApi();
void handleWifiConnector();
void handleMQTTConnector();
void handleRoot(); //Handle Root page ('/')
void handleNotFound(); //Handle page not found

//Server ------------------------------------- 
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void setupServer();

//CONNECTIONS --------------------------------
void configModeCallback (WiFiManager *myWiFiManager); 
bool setupConnection(String _ssid, String _password);
void handleMsg(char *topic, char *msg);
void onMsgReceived(char* topic, byte* payload, unsigned int length);
void reconnect();
 
//SENSORS -------------------------------------
void readDHT11();
void readMQ135();
void readDust();
void publishSensorDataOnInterval(int milisecs);

//OTHERS -------------------------------------- 
void showRGB(int r, int g, int b);
void led();
void buzzer(float f);
void debug(); 
