#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// Pinos dos LEDs
const uint LED_RED = 13, LED_YELLOW = 12, LED_GREEN = 11;

// Estado do semáforo
static uint8_t state = 0;

// Função de callback do timer
bool repiting_timer_callback(struct repeating_timer *t)
{
    if (state == 0)
    {
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 1);
        gpio_put(LED_GREEN, 0);
    }
    else if (state == 1)
    {
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 1);
    }
    else if (state == 2)
    {
        gpio_put(LED_RED, 1);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 0);
    }

    state = (state + 1) % 3; // Incrementa o estado e volta ao início após o último estado
    return true;
}

// Configuração inicial
void setup()
{
    stdio_init_all();

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_put(LED_RED, 1);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN, 0);
}

int main()
{
    setup();

    // Inicializa o timer
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repiting_timer_callback, NULL, &timer);
    while (true)
    {
        printf("State: %d\n", state);
        sleep_ms(1000);
    }

    return 0;
}
