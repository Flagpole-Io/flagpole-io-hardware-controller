//
// Created by David Casey on 11/1/22.
//

#include <pigpio.h>
#include <stdio.h>
#include "gpio.h"

void initializeGpio() {
    printf("[gpio]: initializing gpio library.\n");

    if (gpioInitialise() < 0) {
        printf("[gpio]: error initializing gpio library.\n");
    }

    gpioSetMode(GPIO_RAISE_FLAG, PI_OUTPUT);

    printf("[gpio]: initialized gpio library.\n");
}

void terminateGpio() {
    gpioTerminate();
}

void enableOutput(unsigned int output) {
    gpioWrite(output, 1);
}

void disableOutput(unsigned int output) {
    gpioWrite(output, 0);
}