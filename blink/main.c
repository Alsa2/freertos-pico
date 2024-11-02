#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_PIN1 14 // GPIO pin for the external LED
#define LED_PIN2 15 // Blinking delay in milliseconds

void vBlinkTask1() {
   for (;;) {
      gpio_put(LED_PIN1, 1);
      vTaskDelay(1000);
      gpio_put(LED_PIN1, 0);
      vTaskDelay(1000);
   }
}

void vBlinkTask2() {
   for (;;) {
      gpio_put(LED_PIN2, 1);
      vTaskDelay(500);
      gpio_put(LED_PIN2, 0);
      vTaskDelay(500);
   }
}


void main() {
   gpio_init(LED_PIN1);
   gpio_set_dir(LED_PIN1, GPIO_OUT);
   gpio_init(LED_PIN2);
   gpio_set_dir(LED_PIN2, GPIO_OUT);
   xTaskCreate(vBlinkTask1, "Blink Task 1", 128, NULL, 1, NULL);
   xTaskCreate(vBlinkTask2, "Blink Task 2", 128, NULL, 1, NULL);
   vTaskStartScheduler();
}
