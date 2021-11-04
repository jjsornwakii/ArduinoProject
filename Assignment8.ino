#include <Arduino_FreeRTOS.h>
#include "queue.h"
#define RED 6
#define YELLOW 7
#define GREEN 8
#define SW1 4
#define SW2 3
#define SW3 2
QueueHandle_t ledQueue;

bool YELLOWBlink,GREENON,GREENBlink;
long RedTime = 0;
long GreenTime = 0;
int count = 0;
void setup()
{
  Serial.begin(9600);
  ledQueue = xQueueCreate(15,sizeof(int32_t));
  xTaskCreate(vSenderTask,"Sender RED",100,SW1,1,NULL);
  xTaskCreate(vSenderTask,"Sender YELLOW",100,SW2,1,NULL);
  xTaskCreate(vSenderTask,"Sender GREEN",100,SW3,1,NULL);
  xTaskCreate(vReceiverTask,"Receiver", 100,NULL, 1, NULL);
}
void vSenderTask(void *pvParameters)
{
  int32_t valueToSend = 0;
  int Switch = (int32_t)pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(Switch, INPUT); 

  while(1)
  {
    if(digitalRead(Switch) == 1)
      valueToSend = Switch;
    else
      valueToSend = 0;
    if(valueToSend != 0)
    {
      xQueueSend(ledQueue,&valueToSend,xTicksToWait);
      vTaskDelay(20);
    }
  }
}
void vReceiverTask(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(50);
  pinMode(RED, OUTPUT); digitalWrite(RED, 1);
  pinMode(YELLOW, OUTPUT); digitalWrite(YELLOW, 1);
  pinMode(GREEN, OUTPUT); digitalWrite(GREEN, 1);
  while(1)
  {
    qStatus = xQueueReceive(ledQueue,&valueReceived,xTicksToWait);
    if(qStatus == pdPASS)
    {
      if(valueReceived == SW1)
      {
        RedTime = millis();
      }
      else if(valueReceived == SW2)
      {
        YELLOWBlink = !YELLOWBlink;
      }
      else if(valueReceived == SW3 && GREENON != 1)
      {
        count = 0;
        GREENON = 1;
        GREENBlink = 0;
        GreenTime = millis();
      }
    }
    
    if(millis() - RedTime < 3000)
      digitalWrite(RED, LOW);
    else
      digitalWrite(RED, HIGH);
      
    if(YELLOWBlink == 1)
    {
      digitalWrite(YELLOW, LOW);
      vTaskDelay(10);
      digitalWrite(YELLOW, HIGH);
      vTaskDelay(10);
    }

    if(GREENON == 1 && count < 5)
    {
      if(millis() - GreenTime > 500)
      {
        GREENBlink = !GREENBlink;
        GreenTime = millis();
        count++;
      }
      digitalWrite(GREEN, GREENBlink); 
    }
    else
      GREENON = 0;
  }
}
void loop(){}
