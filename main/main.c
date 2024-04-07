#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define GPIO_LED        2
#define DELAY_MS       1000         



void app_main(void)
{


         // Configuracion de perifericos: gpio
    // Configuro el gpio  GPIO_LED como salida (output)
    gpio_set_direction(GPIO_LED,GPIO_MODE_OUTPUT);



    uint32_t led_status = 0;


    while(1){

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
         vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);

    }

   
}