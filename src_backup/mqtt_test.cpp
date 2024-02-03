#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// WiFi credentials
const char* ssid = "ELF";
const char* password = "0890261083";

// MQTT server details
const char* mqttServer = "mqtt.yourserver.com";
const int mqttPort = 1883;
const char* mqttClientId = "ESP32_Client";

// Topic to subscribe to
const char* subscribeTopic = "esp32/data";

// Create an instance of the WiFiClientSecure class
WiFiClient espClient;
PubSubClient client(espClient);

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void connectToMQTT() {
  Serial.println("Connecting to MQTT...");

  client.setServer(mqttServer, mqttPort);
  
  while (!client.connect(mqttClientId)) {
    Serial.println("Failed to connect to MQTT. Retrying in 5 seconds...");
    delay(5000);
  }

  Serial.println("Connected to MQTT");

  // Subscribe to the specified topic
  client.subscribe(subscribeTopic);
}

void messageReceivedCallback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message received from topic: " + String(topic));

  // Handle the received message here
  Serial.write(payload, length);
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  connectToWiFi();
  connectToMQTT();

  xTaskCreatePinnedToCore(
    loopTask,    /* Function to implement the task */
    "loopTask",  /* Name of the task */
    10000,       /* Stack size in words */
    NULL,        /* Task input parameter */
    1,           /* Priority of the task */
    NULL,        /* Task handle. */
    0            /* Core where the task should run */
  );
}

void loop() {
  // This is the main loop, but it's not used since tasks are being used.
}

void loopTask(void *pvParameters) {
  while (1) {
    // Your custom logic here

    // Example: Publish a message every 10 seconds
    client.publish("esp32/test", "Hello, MQTT!");

    // Handle incoming messages
    client.loop();

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}