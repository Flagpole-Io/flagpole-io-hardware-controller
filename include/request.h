//
// Created by David Casey on 11/1/22.
//

#ifndef FLAGPOLE_IO_HARDWARE_CONTROLLER_REQUEST_H
#define FLAGPOLE_IO_HARDWARE_CONTROLLER_REQUEST_H

#include <hiredis/hiredis.h>

/**
 * Object representing a flagpole hardware request.
 */
struct Request {
    char *action;
    int value;
};

typedef struct Request Request;

/**
 * Gets the current request from the data store.
 * @return
 */
Request *getRequest(redisContext *client);

/**
 * Removes the current request from the data store.
 */
void removeRequest(redisContext *client);

#endif //FLAGPOLE_IO_HARDWARE_CONTROLLER_REQUEST_H
