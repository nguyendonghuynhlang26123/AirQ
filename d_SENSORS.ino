//Read DHT11 h & t data
void readDHT11() {  
  h = dht.readHumidity();    
  t = dht.readTemperature(); 
}

//Read MQ135 sensor CO2 data. About the formula, visit https://github.com/GeorgK/MQ135 library.
void readMQ135() { 
  int val = analogRead(MQ135_PIN); 
  
  float registance = ((1023./(float)val) * 5. - 1.)*10.0;
  float correctedFactor = 0.00035 * t * t - 0.02718 * t + 1.39538 - (h-33.)*0.0018;
  chemical = 116.6020682 * pow(((registance / correctedFactor)/76.63), -2.769034857); 
} 

//Read dust sensors
void readDust(){ 
    int samplingTime = 280;
  int deltaTime = 40;
  int sleepTime = 9680;
 
  float voMeasured = 0;
  float calcVoltage = 0; 

  digitalWrite(DUST_LED_PIN,LOW); // Bật IR LED
  delayMicroseconds(samplingTime);  //Delay 0.28ms
  
  voMeasured = analogRead(DUST_VO_PIN); 
  
  delayMicroseconds(deltaTime); //Delay 0.04ms
  digitalWrite(DUST_LED_PIN,HIGH); // Tắt LED
  delayMicroseconds(sleepTime); //Delay 9.68ms
 
  // Tính điện áp từ giá trị ADC
  calcVoltage = voMeasured * (3.3 / 1024); //Điệp áp Vcc của cảm biến (5.0 hoặc 3.3)
 
  dustDensity = (0.17 * calcVoltage) * 1000;
}

//Publish sensor data every {milisecs} miliseconds 
void publishSensorDataOnInterval(int milisecs){  
    unsigned long now = millis();
    if (now - lastMsg > milisecs) {
      lastMsg = now;   
      snprintf (msg, MSG_BUFFER_SIZE, "%f|%f|%f|%f", h, t, chemical, dustDensity);
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(TOPIC_OUT, msg); 
    }
}
