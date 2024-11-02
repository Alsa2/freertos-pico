#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();
    while (1)
    {
        printf("Hello World From Pi Pico USB CDC\n");
        sleep_ms(100);
    }
}