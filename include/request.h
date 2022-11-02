//
// Created by David Casey on 11/1/22.
//

#ifndef FLAGPOLE_IO_HARDWARE_CONTROLLER_REQUEST_H
#define FLAGPOLE_IO_HARDWARE_CONTROLLER_REQUEST_H

#include <hiredis/hiredis.h>

struct Request {
    char *action;
    int value;
};

typedef struct Request Request;

Request *getRequest(redisContext *);

void removeRequest(redisContext *);

#endif //FLAGPOLE_IO_HARDWARE_CONTROLLER_REQUEST_H
