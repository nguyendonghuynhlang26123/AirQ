//Function for displaying RGB.
void showRGB(int red, int green, int blue)
{ 
  Serial.printf("-->LED: %i %i %i\n", red,green,blue);
  ledcWrite(RED_LED_CHANNEL, red); 
  ledcWrite(BLUE_LED_CHANNEL, green); 
  ledcWrite(GREEN_LED_CHANNEL, blue);
}
 
void led(){ 
  if (isOffline) {
    if (hasNoConnection){ 
      //If no connection => BLINKING
      showRGB(rOff * brightOff, gOff * brightOff, bOff * brightOff);
      delay(500);
      showRGB(0, 0, 0);
      delay(500);
      showRGB(rOff * brightOff, gOff * brightOff, bOff * brightOff);
      delay(500);
      showRGB(0, 0, 0); 
    } else  showRGB(rOff * brightOff, gOff * brightOff, bOff * brightOff);
  }
  else showRGB(r * brightness, g * brightness, b * brightness);
}

void buzzer(float f){
  Serial.print("BUZING");
  Serial.println(f);
  //ledcWriteTone(4, 4500 * f); 
  ledcWrite(BUZZER_CHANNEL, f);
}
 
//Print it to the Serial
void debug(){
  Serial.println("-----------------------------------------------------"); 
  //T & H
  Serial.print("Temperature: ");
  Serial.println(t);               
  Serial.print("Humidity: ");
  Serial.println(h);    

  //CO2
  Serial.print("Chemicals: ");
  Serial.print(chemical);
  Serial.println(" ppm");

  //DUST
  Serial.print("Dust Density: ");
  Serial.println(dustDensity);  
 
  Serial.print("LED:");
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.print(b);
  Serial.print(" - ");
  Serial.println(brightness);
}
