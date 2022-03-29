#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>

#include <ArduinoJson.h>

#include "iothubtransportmqtt.h"

#include "config.h"

static bool messagePending = false;
static bool messageSending = true;

static char *connectionString = DeviceConnStr;
static char *ssid = my_SSID;
static char *pass = my_PWD;

static int interval = INTERVAL;

void initTime()
{
    time_t epochTime;
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    while (true)
    {
        epochTime = time(NULL);

        if (epochTime == 0)
        {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        }
        else
        {
            Serial.printf("Fetched NTP epoch time is: %lu.\r\n", epochTime);
            break;
        }
    }
}

void initWiFi()
{
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  

    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

static IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Demo NodeMCU Azure IOT");

  initTime();
  initWiFi();

  static IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;

  iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, protocol);
  if(iotHubClientHandle == NULL)
  {
    while(1);
  }
  
}

static int messageCount = 1;
void loop() {
  // put your main code here, to run repeatedly:
  if(!messagePending && messageSending){
    char messagePayload[MESSAGE_MAX_LEN];
    bool ValueAlert = readMessage(messageCount, messagePayload);
    SendMessage(iotHubClientHandle, messagePayload, ValueAlert);
    Serial.println("sendMessage Azure IOT");
    messageCount++;
    delay(interval);
  }
  IoTHubClient_LL_DoWork(iotHubClientHandle);
  delay(10);
}
