#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_PIN 15 // GPIO pin for the external LED

void vBlinkTask() {
   for (;;) {
      gpio_put(LED_PIN, 1);
      vTaskDelay(1000);
      gpio_put(LED_PIN, 0);
      vTaskDelay(1000);
   }
}

void main() {
   gpio_init(LED_PIN);
   gpio_set_dir(LED_PIN, GPIO_OUT);
   xTaskCreate(vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
   vTaskStartScheduler();
}
