//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID()); 
}  

bool setupConnection(String _ssid, String _password){
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(_ssid);

    WiFi.begin(_ssid.c_str(), _password.c_str());
    int timeCount = 0;
    int timeOut = 6000; //4 seconds

    while (timeCount < timeOut && WiFi.status() != WL_CONNECTED) {
        delay(500);
        timeCount += 500;
        Serial.print(".");
    }

    if (timeCount >= timeOut){
      Serial.println("WiFi Timeout!");
      return false;
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    return true;
}

//Call back whenever esp detect msg
void onMsgReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  handleMsg(topic, (char *)payload);
}

//Try to reconnect to the broker
void reconnect() { 
  Serial.print("Attempting MQTT connection...");
  // Create a random client ID
  String clientId = "ESP8266Client-";
  clientId += String(random(0xffff), HEX);
  // Attempt to connect
  if (client.connect(clientId.c_str())) {
    Serial.println("connected");  
    client.publish(TOPIC_OUT_PING, "hello"); 

    //Subscribing TOPICs 
    client.subscribe(TOPIC_IN_LED); 
    client.subscribe(TOPIC_IN_PING); 
    client.subscribe(TOPIC_IN_BUZZER);
    client.subscribe(TOPIC_IN_STATE);
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    // Wait 5 seconds before retrying
    delay(5000);
  }
}

void handleMsg(char *topic, char *msg){ 
  if (strcmp(topic, TOPIC_IN_LED) == 0){  
    char* token = strtok(msg, ",");
    r= atoi(token); 
    token= strtok(0, ",");
    g = atoi(token); 
    token = strtok(0, ",");
    b = atoi(token); 
    token = strtok(0, ",");
    if (strcmp(token,"0")==0) brightness = 0;
    else brightness = atof(token); 
  }
  else if (strcmp(topic, TOPIC_IN_BUZZER) == 0){
    buzzer(atof(msg));
  }
  else if (strcmp(topic, TOPIC_IN_PING) == 0){
    isOffline = false;
  }
}
