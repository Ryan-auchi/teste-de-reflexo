#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"

#define GREEN_PIN 11
#define BLUE_PIN 12
#define RED_PIN 13    
#define BTN_PIN 5       


void piscar_led(int vezes, int intervalo_ms, int cor) {
    if(cor == 1){
        for (int i = 0; i < vezes; i++) {
            gpio_put(GREEN_PIN, 1);  
            sleep_ms(intervalo_ms);
            gpio_put(GREEN_PIN, 0);  
            sleep_ms(intervalo_ms);
        }
    }else if(cor == 2){
        for (int i = 0; i < vezes; i++) {
            gpio_put(BLUE_PIN, 1);  
            sleep_ms(intervalo_ms);
            gpio_put(BLUE_PIN, 0); 
            sleep_ms(intervalo_ms);
        }
    }else{
        for (int i = 0; i < vezes; i++) {
            gpio_put(RED_PIN, 1); 
            sleep_ms(intervalo_ms);
            gpio_put(RED_PIN, 0);  
            sleep_ms(intervalo_ms);
          
        }
    }
}

int main() {
    stdio_init_all();   

    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);

    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);

    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);

    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    printf("Jogo de Reação - Pressione o botão quando o LED acender!\n");

    while (1) {
        
        int delay_ms = rand() % 4000 + 1000; 
        sleep_ms(delay_ms);

        gpio_put(GREEN_PIN, 1);
        uint64_t start_time = time_us_64(); 

        while (gpio_get(BTN_PIN)) {
            tight_loop_contents(); 
        }

        gpio_put(GREEN_PIN, 0);

        uint64_t end_time = time_us_64();
        uint64_t reaction_time = end_time - start_time;
        float reaction_time_ms = (float)reaction_time / 1000;

        printf("Tempo de reação: %.2f ms\n", reaction_time_ms);
        
        if (reaction_time_ms < 190) {
            printf("Reflexo rápido!\n");
            piscar_led(4, 100, 1);
        } else if (reaction_time_ms < 290) {
            printf("Reflexo médio!\n");
            piscar_led(4, 100, 2);
        } else {
            printf("Reflexo lento!\n");
            piscar_led(4, 100, 3);  
        }

        sleep_ms(1000);
    }
}