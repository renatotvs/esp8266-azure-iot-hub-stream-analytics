# LAB: NodeMCU ESP8266 - Azure IoT Hub, Stream Analytics e Blob Storage

**Objetivo deste Laboratório:**

Conectar a placa NodeMCU v3 Esp8266 para integrar ao Azure IOT Hub e aos serviços Stream Analytics e Azure Blob Storage.

**Componentes utilizados:**
+ Device: Placa NodeMCU ESP8266
+ Potenciômetro

**Cenário**

![image](https://user-images.githubusercontent.com/42357180/160649317-bd5b9dd5-f8dc-4881-b169-b752374759bd.png)

**Importante:**

Para executar este lab é aconselhável que tenha boa familiaridade com a Azure para as configurações abaixo.

**Configurações Azure:**

1) criar recurso IoT Hub
2) criar novo device
3) criar recurso Stream Analytics
4) criar recurso Blob Storage
5) criar um novo container
6) configurar o Stream analytics (entre IoT Hub e blob storage - container)

**Plataforma desenvolvimento - Arduino**
  + instalar as bibliotecas para comunicação com Azure ioT Hub:
    + AzureIoTHub
    + AzureIoTProtocol_MQTT
    + AzureIoTUtility

  ![image](https://user-images.githubusercontent.com/42357180/160653305-c49cb487-9546-41ec-9b90-fd56b5cb1a18.png)
  
  ![image](https://user-images.githubusercontent.com/42357180/160653744-185c765e-4a9d-423e-bf7b-05c407bde374.png)
  
  Garantir que as bibliotecas acima estejam instaladas.
  
  Antes de executar demais etapas no Arduino é necessário efetuar algumas modificações no ambiente de desenvolvimento (essa etapa evita que tenha erros futuros na execução do projeto): 
  https://github.com/renatotvs/esp8266-azure-iot-hub-stream-analytics/blob/main/leia-me.txt
  
  + **Arquivos:**
  
    + **AzureIoTHubLabDemo1.ino** -  arquivo principal que efetua a conexão com wifi da rede configurada e executa o envio da mensagem ao IoT Hub.
    + **config.h** - contém os parâmetros que precisam ser configurados:
      + connection string do "Device" do IoT Hub criado
      + dados de acesso a rede wi-fi
      + pino de comunicação com a placa nodeMCU
      + etc.
    + **iotHubClient.ino** - contém método que dispara a mensagem para Azure IoT Hub.
    + **message.ino** - contém método que efetua leitura do componente configurado no pino da placa que nesse caso estamos usando um potenciômetro como exemplo, poderia ser usado algum outro dispositivo: sensor de temperatura, umidade, etc.

## Ligação dos pinos do potenciômetro a placa NodeMCU Esp8266

![image](https://user-images.githubusercontent.com/42357180/160703173-52e9c572-935d-43ce-9d7e-861969ff8d12.png)

**Explicação pinos:**

+ Primeiro pino "entrada de sinal" é ligado o VCC(5 volts) na porta VIN.
+ Segundo pino "saída do sinal" ou "output" ligado a porta analógica "A0".
+ Terceiro pino "terra" ligado a porta GND.

## Execução do projeto Arduino com a placa NodeMCU

+ Selecionar a placa e porta para execução:

![image](https://user-images.githubusercontent.com/42357180/160689100-543ab7ad-78a1-4057-b45a-d86424398301.png)

![image](https://user-images.githubusercontent.com/42357180/160690332-089e5349-ec66-484b-99b4-1d03dc45180c.png)


+ Fazer upload do código para a placa:

![image](https://user-images.githubusercontent.com/42357180/160687722-8204f460-9d22-4763-bcad-ec48f8e3ddda.png)

+ Acompanhamento do processo do upload do código antes de conectar a rede wifi:

![image](https://user-images.githubusercontent.com/42357180/160689507-d16c27bd-30a2-42f3-b581-a36c44ebba32.png)

+ Visualizar a execução pelo "Serial Monitor" e o momento que a placa é conectado a rede wi-fi:

![image](https://user-images.githubusercontent.com/42357180/160686634-301440b5-d08a-4bc0-8580-72ee7e6a5dc7.png)

![image](https://user-images.githubusercontent.com/42357180/160691272-7707dae7-ae09-4205-b1db-54ad877faf55.png)

A imagem acima mostra quando o wi-fi foi estabelecido com sucesso o processo enviou mensagens ao IoT Hub.

## Acompanhamento da integração com IoT Hub

**IoT Hub**

![image](https://user-images.githubusercontent.com/42357180/160660183-64d0b0ab-516d-43a7-9b8f-40228696e629.png)

**Stream Analytics**

No painel abaixo é possível acompanhar em tempo real os eventos processados e integradas ao blob storage.
![image](https://user-images.githubusercontent.com/42357180/160661942-2bf770f0-9d06-4bb5-963c-777f8be36767.png)

**Container Blob Storage**

No container é armazenado um arquivo .json de forma incremental. Sempre que o houver uma nova integração com o IoT Hub, será processado pelo Stream Analytics o envio dos dados ao container do blob storage.
![image](https://user-images.githubusercontent.com/42357180/160661344-7fee93fd-41cd-495b-af26-8c2d49d3a7eb.png)

**Visualização do arquivo json**
![image](https://user-images.githubusercontent.com/42357180/160664235-ebaea27f-114b-448a-93f7-9d0c86eddc7b.png)

**A coluna Valor** - é o dado que vem do potenciômetro ligado a placa NodeMCU, a cada movimento que faço no potenciômetro a cada 3 segundos é enviado um novo valor.

**Observações**

Fique a vontade para mudar o parãmetro de configuração do tempo de 3 segundos ou mesmo incluir novos componentes de medição.
Esse laboratório é apenas uma ideia de como integrar a placa NodeMCU com Azure IoT Hub.
É possível aplicar a diversos cenários da internet das coisas (iot) como coleta de sensores, telemetria, etc.
