#include <Arduino.h>
//sensor library
#include <DHT.h>
//include Wifi library
#include <WiFi.h>
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
//MQTT library
#include <AsyncMqttClient.h>
//setup sensors connected to device
#define DHT_SENSOR_PIN  DEVICE_PIN_NUMBER 
#define DHT_SENSOR_TYPE TEMP_SENSOR_TYPE
#define SOIL_SENSOR_PIN  SOIL_PIN_NUMBER 
#define DEVICE DEVICE_NAME
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//connect to wifi
#define WIFI_SSID SECRET_SSID
#define WIFI_PASSWORD SECRET_PASSWORD
// Digital Ocean MQTT Mosquitto Broker
#define MQTT_HOST IPAddress(ADD_IP_ADDRESS)
#define MQTT_PORT 1883
#define MQTT_USERNAME SECRET_MQTT_USERNAME
#define MQTT_PASSWORD SECRET_MQTT_PASSWORD
//MQTT topics
#define MQTT_PUB_TEMP MQTT_TOPIC_ONE 
#define MQTT_PUB_HUM MQTT_TOPIC_TWO  
#define MQTT_PUB_SOIL MQTT_TOPIC_THREE

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 5000;         // Interval at which to publish sensor readings

int i = 0;

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(10000);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      connectToMqtt();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
      xTimerStart(wifiReconnectTimer, 0);
      break;
  }
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
// Do whatever you want when you receive a message Serial.println("Publish received."); Serial.print(" topic: ");
  Serial.println(topic);
  Serial.print(" qos: "); 
  Serial.println(properties.qos); 
  Serial.print(" dup: "); 
  Serial.println(properties.dup); 
  Serial.print(" retain: "); 
  Serial.println(properties.retain); 
  Serial.print(" len: "); 
  Serial.println(len); 
  Serial.print(" index: "); 
  Serial.println(index); 
  Serial.print(" total: "); 
  Serial.println(total);
}

void onMqttPublish(uint16_t packetId) {
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void setup() {
  Serial.begin(115200);
  dht_sensor.begin();
  Serial.println();

  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCredentials(MQTT_USERNAME, MQTT_PASSWORD);
  connectToWifi();
}

void loop() {
  float humi  = dht_sensor.readHumidity();
  //remove true to get temperature in Celsuis
  float f = dht_sensor.readTemperature(true);
  int soil_num = analogRead(A0);
  int soil = map(soil_num, wet, dry, 100, 0);
  if ( isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.println("%");
    Serial.print("Temp: ");
    Serial.println(f);
    Serial.print("soil: ");
    Serial.println(soil);
  }
  unsigned long currentMillis = millis();
  // Every X number of seconds (interval = 5 seconds) 
  // it publishes a new MQTT message
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(f).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i", MQTT_PUB_TEMP, packetIdPub1);
    Serial.printf("Message: %.2f \n", f);
    uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_HUM, 1, true, String(humi).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId %i: ", MQTT_PUB_HUM, packetIdPub2);
    Serial.printf("Message: %.2f \n", humi);
    uint16_t packetIdPub3 = mqttClient.publish(MQTT_PUB_SOIL, 1, true, String(soil).c_str());
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i", MQTT_PUB_SOIL, packetIdPub3);
    Serial.printf("Message: %.3f \n", soil);
  }
  delay(10000);
}
