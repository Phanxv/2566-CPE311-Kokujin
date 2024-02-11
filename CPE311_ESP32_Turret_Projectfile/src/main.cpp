#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/*----------------Initialize WiFi and MQTT conncetion----------------*/

// WiFi credentials
const char *ssid = "furue";
const char *password = "Delta_006";

// MQTT server details
const char *mqttServer = "192.168.117.214";
const int mqttPort = 1883;
const char *mqttClientId = "ESP32_Client";

// Topic to subscribe to
const char *subscribeTopic = "ControlApp/Command";

// Create an obj of the WiFiClient class
WiFiClient espClient;
PubSubClient client(espClient);

int command_flag = 0;
String payload_str;

/*----------------Initialize Servo Objects and variables----------------*/

Servo servoX, servoY, servoTrig; 

int servoX_pos = 90; 
int servoY_pos = 0;
int servoTrig_pos = 180;

int servoX_pin = 18;
int servoY_pin = 19;
int servoTrig_pin = 17;

/*----------------Initialize variables for Motor Driver----------------*/
int ENA_pin = 1;
int IN1_pin = 22;
int IN2_pin = 23;

/*----------------Initialize reset pin----------------*/
int RST_pin = 12;

/*----------------Function prototype declaration----------------*/

void Init_Config();
void connectToWiFi();
void connectToMQTT();
void messageReceivedCallback(char *topic, byte *payload, unsigned int length);

void clientTask(void *pvParameters);
void actionTask(void *pvParameters);

void setup()
{
    Serial.begin(115200);
    Init_Config();
    connectToWiFi();
    connectToMQTT();

	/*-------Create task and pinned to different core-------*/

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

void Init_Config(){
    
    /*-------Allocate config pin mode for Motor Driver-------*/

    pinMode(ENA_pin, OUTPUT);
    pinMode(IN1_pin, OUTPUT);
    pinMode(IN2_pin, OUTPUT);
    digitalWrite(ENA_pin, LOW);
    digitalWrite(IN1_pin, LOW);
    digitalWrite(IN2_pin, LOW);

	/*-------Allocate PWM timer and config servo-------*/

	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servoX.setPeriodHertz(50);    // standard 50 hz servo
	servoX.attach(servoX_pin, 771, 3036);
  	servoY.setPeriodHertz(50);    // standard 50 hz servo
	servoY.attach(servoY_pin, 771, 3036);
    servoTrig.setPeriodHertz(50);
    servoTrig.attach(servoTrig_pin, 771, 3036);
}

void resetPosition(){
    servoX_pos = 90;
    servoY_pos = 0;
    servoTrig_pos = 180;
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
  if(payload_str == "UP"){
    command_flag = 1;
    Serial.println("command_flag = 1");
  }
  else if(payload_str == "DOWN"){
    command_flag = 2;
    Serial.println("command_flag = 2");
  }
  else if(payload_str == "RIGHT"){
    command_flag = 3;
    Serial.println("command_flag = 3");
  }
  else if(payload_str == "LEFT"){
    command_flag = 4;
    Serial.println("command_flag = 4");
  }
  else if(payload_str == "SHOOT"){
    command_flag = 5;
    Serial.println("command_flag = 5");
  }
  else if(payload_str == "STOP"){
    command_flag = 0;
    Serial.println("command_flag = 0");
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
        switch (*pvPayload)
        {
            case 0:
                servoX.write(servoX_pos);
                servoY.write(servoY_pos);
                servoTrig.write(servoTrig_pos);
                digitalWrite(ENA_pin, HIGH);
                digitalWrite(IN1_pin, HIGH);
                digitalWrite(IN2_pin, LOW);
                vTaskDelay(20 / portTICK_PERIOD_MS);
                break;
            case 1:
                if(servoY_pos <= 45){
                    servoY_pos++;
                }
                servoY.write(servoY_pos);
                vTaskDelay(20 / portTICK_PERIOD_MS);
                break;
            case 2:
                if(servoY_pos > 0){
                    servoY_pos--;
                }
                servoY.write(servoY_pos);
                vTaskDelay(20 / portTICK_PERIOD_MS);
                break;
            case 3:
                if(servoX_pos > 0){
                    servoX_pos--;
                }
                servoX.write(servoX_pos);
                vTaskDelay(20 / portTICK_PERIOD_MS);
                break;
            case 4:
                if(servoX_pos <= 180){
                    servoX_pos++;
                }
                servoX.write(servoX_pos);
                vTaskDelay(20 / portTICK_PERIOD_MS);
                break;
            case 5:
                if(servoTrig_pos > 60){
                    servoTrig_pos--;
                }
                else{
                    servoTrig_pos = 180;
                }
                servoTrig.write(servoTrig_pos);
                vTaskDelay(10 / portTICK_PERIOD_MS);
                break;
            default:
                break;
        }
    }
}