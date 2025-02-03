#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"
#include "pio_matrix.pio.h"

void numbers(int number, uint32_t valor_led, PIO pio, uint sm);
void gpio_irq_handler(uint gpio, uint32_t events);
void blink(uint led, uint32_t time);

#define OUT_PIN 7
#define NUM_PIXELS 25
#define RED_LED_PIN 13
#define BUTTON_A 5
#define BUTTON_B 6

static volatile uint32_t last_time = 0; 
static volatile int cont = 0;
PIO pio;
uint sm;
uint32_t valor_led;


void init(){
    //inicializar o led
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    //inicializar o botão para incrementar - GPIO5
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    //inicializar o botão para decrementar - GPIO6
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}




void imprimir_binario(int num)
{
    int i;
    for (i = 31; i >= 0; i--){
        (num & (1 << i)) ? printf("1") : printf("0");
    }
}

uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        valor_led = matrix_rgb(desenho[24 - i] * b, desenho[24 - i] * r, desenho[24 - i] * g);
        pio_sm_put_blocking(pio, sm, valor_led);
    }

    imprimir_binario(valor_led);
}




void blink(uint led, uint32_t time){
    gpio_put(RED_LED_PIN, true);
    sleep_ms(time/2);
    gpio_put(RED_LED_PIN, false);
    sleep_ms(time/2);
}


void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // 300 ms de debouncing
    if(current_time - last_time > 300000){ 
        if(gpio == BUTTON_A && cont < 9){
            cont++;
        }else if(gpio == BUTTON_B && cont > 0){
            cont--;
        }
        last_time = current_time;
        numbers(cont, valor_led, pio, sm);
    
    }
}



// Função Principal
int main(){
    init();

    pio = pio0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    numbers(cont, valor_led, pio, sm);

    while (true){
        blink(RED_LED_PIN, 200);
    }
}



void numbers(int number, uint32_t valor_led, PIO pio, uint sm){

    double zero[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};
    
    double one[25] = {
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 0.0,
        1.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0};

    double two[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    double three[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    double four[25] = {
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0};

    double five[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};
    
    double six[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};
    
    double seven[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0};
   
    double eight[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};
   
    double nine[25] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};


    switch(number){
        case 0:
            desenho_pio(zero, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 1:
            desenho_pio(one, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 2:
            desenho_pio(two, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 3:
            desenho_pio(three, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 4:
            desenho_pio(four, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 5:
            desenho_pio(five, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 6:
            desenho_pio(six, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 7:
            desenho_pio(seven, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 8:
            desenho_pio(eight, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;
        case 9:
            desenho_pio(nine, valor_led, pio, sm, 0.0, 0.0, 1.0);
            break;    
    }

}
