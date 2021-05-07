//LIBRARY ----------------------
#include <DHT.h>  
#include "WiFi.h"
#include <PubSubClient.h>
#include <WiFiManager.h> 
#include <WebServer.h>

//CONSTANTS -----------------
#define PORT 1883
#define MSG_BUFFER_SIZE  (50)

//PINS ----------------------- 
#define DUST_VO_PIN 32
#define MQ135_PIN 33 
#define DHT_PIN 25
#define DUST_LED_PIN 26

#define BUZZER_PIN 13
#define RED_PIN 27
#define GREEN_PIN 14
#define BLUE_PIN 12


//TYPES ---------------------
#define DHT_TYPE DHT11

//TOPICS ------------------
#define TOPIC_OUT "136_118_269/OUT" 
#define TOPIC_OUT_LED "136_118_269/OUT/LED" 
#define TOPIC_OUT_PING "136_118_269/OUT/PING"
#define TOPIC_IN_PING "136_118_269/IN/PING"
#define TOPIC_IN_LED "136_118_269/IN/LED" 
#define TOPIC_IN_BUZZER "136_118_269/IN/BUZZER" 
#define TOPIC_IN_STATE "136_118_269/IN/STATE"

//CHANNELS
#define RED_LED_CHANNEL 1
#define GREEN_LED_CHANNEL 2
#define BLUE_LED_CHANNEL 3
#define BUZZER_CHANNEL 4

//GLOBAL VARIABLES  ---------------------
DHT dht(DHT_PIN, DHT_TYPE);  
WiFiClient espClient;
PubSubClient client(espClient); 
WebServer server(136);
const char* mqtt_server = "broker.mqtt-dashboard.com";
char msg[MSG_BUFFER_SIZE]; 
unsigned long lastMsg = 0;

/* Put your SSID & Password */
const char* ssid = "ESP32_G16";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

//VARIABLES ----------------------
//SENSORS
float h = -1;
float t = -1;
float chemical = -1;  
float dustDensity = -1;

//OTHERS
int r = 150, g = 82, b=40;
float brightness = 1;

//OFFLINES
bool isOffline = true; 
bool hasNoConnection = true;
int rOff = 150, gOff = 82, bOff = 40;
float brightOff = 1;
