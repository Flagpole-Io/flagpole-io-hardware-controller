//
// Created by David Casey on 11/1/22.
//

#ifndef FLAGPOLE_IO_HARDWARE_CONTROLLER_GPIO_H
#define FLAGPOLE_IO_HARDWARE_CONTROLLER_GPIO_H

#define GPIO_RAISE_FLAG 5
#define GPIO_LOWER_FLAG 6
#define GPIO_UPPER_LIMIT 13
#define GPIO_LOWER_LIMIT 19
#define GPIO_ENABLE_LIGHTS 26

void initializeGpio();

void terminateGpio();

void enableOutput(unsigned int output);

void disableOutput(unsigned int output);

#endif //FLAGPOLE_IO_HARDWARE_CONTROLLER_GPIO_H
