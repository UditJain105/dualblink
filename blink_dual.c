#include "blink_dual.h"
#include <stdio.h>
#include  "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define led1 2
#define led2 13
TaskHandle_t Task1;
TaskHandle_t Task2;

void blink1( void * parameter ){
  printf("Task1 is running on core %d\n",xPortGetCoreID());

  for(;;){
    gpio_set_level(led1,1);
    printf("Led1 ON on Core %d\n",xPortGetCoreID());
    vTaskDelay(100);
    gpio_set_level(led1,0);
    printf("Led1 OFF on Core %d\n",xPortGetCoreID());
    vTaskDelay(100);
  } 
}

void blink2( void * parameter ){
    printf("Task1 is running on core %d\n",xPortGetCoreID());

  for(;;){
    gpio_set_level(led2,1);
    printf("Led2 ON on Core %d\n",xPortGetCoreID());
    vTaskDelay(50);
    gpio_set_level(led2,0);
    printf("Led2 OFF on Core %d\n",xPortGetCoreID());
    vTaskDelay(50);
  } 
}

void blink_dual(void)
{
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    gpio_set_direction(led2, GPIO_MODE_OUTPUT);
    xTaskCreatePinnedToCore(blink1,"Task1",10000,NULL,1,&Task1,0);
    xTaskCreatePinnedToCore(blink2,"Task2",10000,NULL,1,&Task2,1);
}

