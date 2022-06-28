#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t myTask1Handle = NULL;

void myTask1 (void *p){
		
		int count =(int*) p;
		while(1){
			printf("hello, world! : %d\r\n", count++);
			vTaskDelay(1000);
			
			if (count == 31){
					vTaskDelete(myTask1Handle);
			}
		}
}


int main(void){
	int pass = 25;
	
	xTaskCreate(myTask1, "task1", 200, (void*) pass, tskIDLE_PRIORITY, &myTask1Handle);
	
	vTaskStartSchduler();
	
}
