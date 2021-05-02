void handleGetState(){
  readMQ135();
  readDHT11();
  readDust(); 
  String res = String(h) + " , " + String(t) + " , " + String(chemical) + " , " + String(dustDensity);
  server.send(200, "text/plain", res);
}
void handleDisconnectApi(){
  WiFi.disconnect();
  server.send(200, "text/plain", "DISCONNECT SUCCESSFULLY");
} 
void handleLedApi(){
  if (!isOffline) {
    server.send(400, "text/plain", "Cannot make command when the device is in ONLINE mode");
    return;
  }
  String sRed = server.arg("red");
  String sGreen = server.arg("green");
  String sBlue = server.arg("blue");
  
  Serial.printf("Received Color: %s  %s  %s\n", sRed, sGreen, sBlue); 
  rOff = sRed.toInt();
  gOff = server.arg("green").toInt();
  bOff = server.arg("blue").toInt();
  brightOff = server.arg("brightness").toFloat();  

  Serial.print("------------>");
  Serial.printf("Color: %i, %i, %i\n", rOff,gOff,bOff);

  Serial.print("------------>");
  Serial.printf("Brightness: %f\n", brightOff); 

  server.send(200, "text/plain", "Successfully");
}

void handleWifiConnector(){
  if (!isOffline) {
    server.send(400, "text/plain", "Cannot make command when the device is in ONLINE mode");
    return;
  }
  String pSsid = server.arg("ssid");
  String pPassword = server.arg("password"); 
  
  bool res = setupConnection(pSsid, pPassword);
  if (res) server.send(200, "text/plain", "Connect successfully");
  else server.send(400, "text/plain", "Connect Failed! Please check credensials again");
  
  isOffline = false;
}

void handleMQTTConnector(){
  if (client.connected()) server.send(200, "text/plain", "ONLINE");
  else server.send(400, "text/plain", "OFFLINE");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Station connected");
  hasNoConnection = false;  
}

void setupServer(){
   WiFi.softAP(ssid, password);
   WiFi.softAPConfig(local_ip, gateway, subnet);
   WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
   delay(100);

   server.on("/", handleRoot);
   server.on("/sensors", handleSensorPage);
   server.on("/wifi-config", handleWifiConfigPage);
   server.on("/api/state", handleGetState);
   server.on("/api/wifi", handleWifiConnector); 
   server.on("/api/mqtt", handleMQTTConnector); 
   server.on("/api/led-config", handleLedApi);
   server.on("/api/disconnect", handleDisconnectApi); 
   server.onNotFound(handleNotFound);
   server.begin();
   Serial.println("HTTP server started");
}
