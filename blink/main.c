#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define LED_PIN1 15 // GPIO pin for the external LED

static QueueHandle_t xQueue = NULL;

void vBlinkTask() {
   uint uIValueToSend = 0;
   for (;;) {
      gpio_put(LED_PIN1, 1);
      uIValueToSend = 1;
      xQueueSend(xQueue, &uIValueToSend, 0);
      vTaskDelay(1000);
      gpio_put(LED_PIN1, 0);
      uIValueToSend = 0;
      xQueueSend(xQueue, &uIValueToSend, 0);
      vTaskDelay(1000);
   }
}

void vUsbTask(void *pvParameters) {
   for (;;) {
      uint uIReceivedValue = 0;
      xQueueReceive(xQueue, &uIReceivedValue, portMAX_DELAY);
      printf("Received value: %d\n", uIReceivedValue);
   }
}

void main() {
   xQueue = xQueueCreate(1, sizeof(uint));

   gpio_init(LED_PIN1);
   gpio_set_dir(LED_PIN1, GPIO_OUT);
   xTaskCreate(vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
   xTaskCreate(vUsbTask, "USB Task", 128, NULL, 1, NULL);
   vTaskStartScheduler();
}
