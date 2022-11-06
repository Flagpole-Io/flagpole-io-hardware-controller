//
// Created by David Casey on 11/1/22.
//

#ifndef FLAGPOLE_IO_HARDWARE_CONTROLLER_DATA_STORE_H
#define FLAGPOLE_IO_HARDWARE_CONTROLLER_DATA_STORE_H

#include <hiredis/hiredis.h>

/**
 * Gets a data store client.
 * @return The data store client.
 */
redisContext *getDataStoreClient();

/**
 * Gets the first element from an array in the data store.
 * @param key The key of the array.
 * @param client The data store client.
 * @return The first element if present, null otherwise.
 */
char *getFirstElementFromArray(char *key, redisContext *client);

/**
 * Removes the first element from an array in the data store.
 * @param key The key of the array.
 * @param client The data store client.
 */
void removeFirstElementFromArray(char *key, redisContext *client);

/**
 * Sets the value of a hasp map field in the data store.
 * @param key The key of the hash map.
 * @param field The key of the field.
 * @param value The value to set.
 * @param client The data store client.
 */
void setHashField(char *key, char *field, char *value, redisContext *client);

#endif //FLAGPOLE_IO_HARDWARE_CONTROLLER_DATA_STORE_H
