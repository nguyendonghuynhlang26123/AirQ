void setup()
{ 
  Serial.begin(115200); 
  WiFi.mode(WIFI_STA);
  Serial.setDebugOutput(true); 
  
  //OTHERS 
  pinMode(MQ135_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(DUST_VO_PIN, INPUT);
  pinMode(DUST_LED_PIN, OUTPUT);
  
  //DHT 
  dht.begin(); 
 
  //LED
  ledcAttachPin(RED_PIN, RED_LED_CHANNEL); // assign RGB led pins to channels
  ledcAttachPin(BLUE_PIN, BLUE_LED_CHANNEL);
  ledcAttachPin(GREEN_PIN, GREEN_LED_CHANNEL);

  ledcSetup(RED_LED_CHANNEL, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(BLUE_LED_CHANNEL, 12000, 8);
  ledcSetup(GREEN_LED_CHANNEL, 12000, 8);

  //BUZZER 
  ledcSetup(BUZZER_CHANNEL, 2000, 8); 
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
 
  //WIFI
  //setup_wifi();
  client.setServer(mqtt_server, PORT);
  client.setCallback(onMsgReceived);
  setupServer();
}

void loop()
{   
    server.handleClient();
    //MQTT
    if (!isOffline){
      while (!client.connected()) {
        reconnect();
      }
      client.loop();
      publishSensorDataOnInterval(2000);
    }
    
    //SENSORS 
    // Monitoring in 1 seconds
    float hAvg = 0, tAvg = 0, chemAvg = 0, dustAvg = 0;
    for (int i = 0; i < 10; i++){
      readMQ135();
      readDHT11();
      readDust(); 

      hAvg += h;
      tAvg += t;
      chemAvg += chemical;
      dustAvg += dustDensity;
      delay(100);
    }

    h = hAvg / 10.0;
    t = tAvg / 10.0;
    chemical = chemAvg / 10.0;
    dustDensity = dustAvg / 10.0;

    //OTHERS
    //debug(); 
    
    led(); 
}
