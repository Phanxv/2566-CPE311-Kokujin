#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// WiFi credentials
const char *ssid = "ELF_2G";
const char *password = "0890261083";

// MQTT server details
const char *mqttServer = "192.168.1.33";
const int mqttPort = 1883;
const char *mqttClientId = "ESP32_Client";

// Topic to subscribe to
const char *subscribeTopic = "esp32/data";

// Create an obj of the WiFiClient class
WiFiClient espClient;
PubSubClient client(espClient);

int command_flag = 0;
String payload_str;

void GPIO_Init();
void connectToWiFi();
void connectToMQTT();
void messageReceivedCallback(char *topic, byte *payload, unsigned int length);

void clientTask(void *pvParameters);
void actionTask(void *pvParameters);

void setup()
{
    Serial.begin(115200);
    GPIO_Init();
    connectToWiFi();
    connectToMQTT();

    xTaskCreatePinnedToCore(
        clientTask,   /* Function to implement the task */
        "clientTask", /* Name of the task */
        10000,        /* Stack size in words */
        NULL,         /* Task input parameter */
        1,            /* Priority of the task */
        NULL,         /* Task handle. */
        0             /* Core where the task should run */
    );
    xTaskCreatePinnedToCore(
        actionTask,   /* Function to implement the task */
        "actionTask", /* Name of the task */
        10000,        /* Stack size in words */
        (int *)&command_flag,         /* Task input parameter */
        1,            /* Priority of the task */
        NULL,         /* Task handle. */
        1             /* Core where the task should run */
    );
}

void loop() {}

void GPIO_Init(){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void connectToWiFi()
{
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
}

void connectToMQTT()
{
    Serial.println("Connecting to MQTT...");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(messageReceivedCallback);

    while (!client.connect(mqttClientId))
    {
        Serial.println("Failed to connect to MQTT. Retrying in 5 seconds...");
        delay(5000);
    }

    Serial.println("Connected to MQTT");

    // Subscribe to the specified topic
    client.subscribe(subscribeTopic);
}

void messageReceivedCallback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  Serial.println("Message received from topic: " + String(topic));
  Serial.write(payload, length);
  Serial.println();
  payload_str = (char*)payload;
  if(payload_str == "ON"){
    command_flag = 1;
    Serial.println("command_flag = 1");
  }
  else if(payload_str == "OFF"){
    command_flag = 2;
    Serial.println("command_flag = 2");
  }
}

void clientTask(void *pvParameters)
{
    while (1)
    {
        client.loop();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void actionTask(void *pvParameters)
{
    while (1)
    {
        int *pvPayload = (int *)pvParameters;
        if(*pvPayload == 1)
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else if(*pvPayload == 2)
        {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}