
#include <ArduinoJson.h>

/*#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>*/

bool readMessage(int messageId, char *payload){
  int Lectura = 0;
  // lecturas que deseas enviar al IoT hub

  int obtenerADC = analogRead(PINADC);

  Lectura = obtenerADC; //Messaje a enviar

  //Para utilizar StaticJsonBuffer nesse exemplo foi necessário atualizar a biblioteca ArduinoJason.h para versão 5.0
  StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["deviceId"] = DEVICE_ID;
  root["messageId"] = messageId;
  bool ValueAlert = false;

  if(std::isnan(Lectura)){
    root["Valor"] = NULL;
  }
  else{
    root["Valor"] = Lectura;
    if(Lectura > VALUE_ALERT){
      ValueAlert = true;
    }
  }

  root.printTo(payload, MESSAGE_MAX_LEN);
  return ValueAlert;
  
}

void parseTwinMessage(char *message){
  StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(message);
  if(!root.success()){
    return;
  }

  if(root["desired"]["interval"].success()){
    interval = root["desired"]["interval"];
  }
  else if(root.containsKey("interval")){
    interval = root["interval"];
  }
}
