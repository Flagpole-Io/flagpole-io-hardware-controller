//
// Created by David Casey on 11/1/22.
//

#ifndef FLAGPOLE_IO_HARDWARE_CONTROLLER_DATA_STORE_H
#define FLAGPOLE_IO_HARDWARE_CONTROLLER_DATA_STORE_H

#include <hiredis/hiredis.h>

redisContext *getDataStoreClient();

char *getFirstElementFromArray(char *key, redisContext *client);

void removeFirstElementFromArray(char *key, redisContext *client);

void setHashField(char *key, char* field, char* value, redisContext *client);

#endif //FLAGPOLE_IO_HARDWARE_CONTROLLER_DATA_STORE_H
