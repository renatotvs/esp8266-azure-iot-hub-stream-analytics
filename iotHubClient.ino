static WiFiClientSecure sslClient; // for ESP8266

const char *onSuccess = "\"Successfully invoke device method\"";
const char *notFound = "\"No method founf\"";

static void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback){
  if(IOTHUB_CLIENT_CONFIRMATION_OK == result){
    messagePending = false;
  }

  messagePending = false;
}

static void SendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *buffer, bool ValueAlert){
  IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char *)buffer, strlen(buffer));
  if(messageHandle == NULL){
    messagePending = false;
  }else{
    MAP_HANDLE properties = IoTHubMessage_Properties(messageHandle);
    Map_Add(properties, "Value Alert", ValueAlert ? "true" : "false");
    if(IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, NULL) == IOTHUB_CLIENT_OK){
      messagePending = true;
    }

    IoTHubMessage_Destroy(messageHandle);
    
  }
}
