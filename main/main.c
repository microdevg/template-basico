#include <stdio.h>


#include "src.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"



#define GPIO_LED        2
#define GPIO_IRQ        18
#define GPIO_MASK        (1ULL << GPIO_IRQ)  // 
#define DELAY_MS        1000         



/*
 * Let's say, GPIO_OUTPUT_IO_0=18, GPIO_OUTPUT_IO_1=19
 * 1ULL<<GPIO_OUTPUT_IO_0 is equal to 0000000000000000000001000000000000000000 and
 * 1ULL<<GPIO_OUTPUT_IO_1 is equal to 0000000000000000000010000000000000000000
 * */


//Deshabilita el parpadeo del led.
static int enable = 0;

// Manejo de GPIO usando interrupciones
static void IRAM_ATTR gpio_isr_handler(void* args){
    //printf("Interrupcion activada \n");
    //Habilita el parpadeo del led
    enable = 1;

}



void app_main(void)
{

    // Configurar el modo interrupcion en gpio
    // Interrupcion rising edge : GPIO_INTR_POSEDGE
    // Interrupcion falling edge: GPIO_INTR_NEGEDGE
    // Interrupcion Ambos: GPIO_INTR_ANYEDGE
    printf("Comenzando el programa \n");
    gpio_set_intr_type(GPIO_IRQ,GPIO_INTR_POSEDGE);
    
    // Pull up : OPCIONES GPIO_PULLUP_ONLY, GPIO_PULLDOWN_ONLY , GPIO_PULLUP_PULLDOWN, GPIO_FLOATING
    gpio_set_pull_mode(GPIO_IRQ,GPIO_PULLUP_ONLY);

    //Configurar la funcion que se ejecuta con la interrupcion (handler: manejador)
    gpio_install_isr_service (ESP_INTR_FLAG_IRAM);


    gpio_isr_handler_add(GPIO_IRQ,&gpio_isr_handler,NULL);


    //Habilito interrupciones
    gpio_intr_enable(GPIO_IRQ);

    //io_conf

    // Configuracion de perifericos: gpio
    // Configuro el gpio  GPIO_LED como salida (output)
    gpio_set_direction(GPIO_LED,GPIO_MODE_OUTPUT);



    uint32_t led_status = 0;

    while(1){


        if(enable == 1){
        //Cuando led_status es 0 se apaga el led, caso contrario se enciende.    
        gpio_set_level(GPIO_LED,led_status);

        if(led_status == 0)
        {  led_status = 1;
        }
        else
        { 
            led_status = 0;
        }

        //Esperamos el periodo de tiempo DELAY_MS cuyo valor esta es milisegundos


        }

        
         vTaskDelay(get_value_delay()/ portTICK_PERIOD_MS);

    }

   
}