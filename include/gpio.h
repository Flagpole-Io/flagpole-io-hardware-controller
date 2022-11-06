//
// Created by David Casey on 11/1/22.
//

#ifndef FLAGPOLE_IO_HARDWARE_CONTROLLER_GPIO_H
#define FLAGPOLE_IO_HARDWARE_CONTROLLER_GPIO_H

#define GPIO_RAISE_FLAG 5
#define GPIO_LOWER_FLAG 6
#define GPIO_ENABLE_LIGHTS 26
#define GPIO_UPPER_LIMIT 13
#define GPIO_LOWER_LIMIT 19

/**
 * Initializes the gpio library, correctly setting up gpio pins for the system.
 */
void initializeGpio();

/**
 * Terminates the gpio library.
 */
void terminateGpio();

/**
 * Enables an output by driving it high.
 * @param output The output to enable.
 */
void enableOutput(unsigned int output);

/**
 * Disables an output by driving it low.
 * @param output The output to disable.
 */
void disableOutput(unsigned int output);

/**
 * Reads the current value of an input.
 * @param input The input to read.
 * @return The current value of the input.
 */
int readInput(unsigned int input);

#endif //FLAGPOLE_IO_HARDWARE_CONTROLLER_GPIO_H
