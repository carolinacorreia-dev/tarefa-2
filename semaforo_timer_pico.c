#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos GPIO para os LEDs
#define LED_VERMELHO 11
#define LED_AMARELO  12
#define LED_VERDE    13

// Variável de estado do semáforo
volatile int estado_semaforo = 0;

// Função de callback do temporizador bool repeating_timer_callback(struct repeating_timer *t)
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de alterar o estado
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna o estado do semáforo
    switch (estado_semaforo) {
        case 0:
            gpio_put(LED_VERMELHO, 1);
            break;
        case 1:
            gpio_put(LED_AMARELO, 1);
            break;
        case 2:
            gpio_put(LED_VERDE, 1);
            break;
    }

    // Atualiza o estado para o próximo ciclo
    estado_semaforo = (estado_semaforo + 1) % 3;

    return true; // Retorna true para continuar repetindo o timer
}

int main() {
    // Inicialização dos LEDs
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicialização da comunicação serial
    stdio_init_all();

    // Configuração do temporizador periódico
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (1) {
        printf("Semáforo em operação. Estado atual: %d\n", estado_semaforo);
        sleep_ms(1000); // Espera de 1 segundo para a próxima mensagem
    }

    return 0;
}
