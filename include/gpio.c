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
    gpioSetPullUpDown(GPIO_RAISE_FLAG, PI_PUD_OFF);
    gpioWrite(GPIO_RAISE_FLAG, PI_LOW);
    gpioSetMode(GPIO_LOWER_FLAG, PI_OUTPUT);
    gpioSetPullUpDown(GPIO_LOWER_FLAG, PI_PUD_OFF);
    gpioWrite(GPIO_LOWER_FLAG, PI_LOW);
    gpioSetMode(GPIO_ENABLE_LIGHTS, PI_OUTPUT);
    gpioSetPullUpDown(GPIO_ENABLE_LIGHTS, PI_PUD_OFF);
    gpioWrite(GPIO_ENABLE_LIGHTS, PI_LOW);

    gpioSetMode(GPIO_UPPER_LIMIT, PI_INPUT);
    gpioSetPullUpDown(GPIO_UPPER_LIMIT, PI_PUD_UP);
    gpioSetMode(GPIO_LOWER_LIMIT, PI_INPUT);
    gpioSetPullUpDown(GPIO_LOWER_LIMIT, PI_PUD_UP);

    printf("[gpio]: initialized gpio library.\n");
}

void terminateGpio() {
    gpioTerminate();
}

void enableOutput(unsigned int output) {
    gpioWrite(output, PI_HIGH);
}

void disableOutput(unsigned int output) {
    gpioWrite(output, PI_LOW);
}

int readInput(unsigned int input) {
    return gpioRead(input);
}