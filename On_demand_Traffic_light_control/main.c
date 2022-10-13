/*
 * On_demand_Traffic_light_control.c
 *
 * Created: 10/7/2022 3:24:27 PM
 * Author : abano
 */ 

//#include <avr/io.h>
#include "APP/APP.h"

int main(void)
{
	APP_vidInit();
    /* Replace with your application code */
    while (1) 
    {
		APP_vidStart();
    }
}

