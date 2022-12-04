//
// Created by David Casey on 11/1/22.
//

#include <stdlib.h>
#include <string.h>
#include "data-store.h"

redisContext *getDataStoreClient() {
    printf("[redis]: getting redis environment.\n");

    char *redisHost = getenv("REDIS_HOST");
    int redisPort = atoi(getenv("REDIS_PORT"));

    printf("[redis]: connecting to redis host %s:%d.\n", redisHost, redisPort);
    redisContext *client = redisConnect(redisHost, redisPort);

    if (client->err) {
        printf("[redis]: connection error: %s\n", client->errstr);
        exit(EXIT_FAILURE);
    }

    printf("[redis]: successfully created connection.\n");
    return client;
}

char *getFirstElementFromArray(char *key, redisContext *client) {
    redisReply *reply = redisCommand(client, "LRANGE %s 0 0", key);

    if (reply->type == REDIS_REPLY_ERROR) {
        printf("[redis]: error: %s\n", reply->str);
    }

    if (reply->type != REDIS_REPLY_ARRAY) {
        printf("[redis]: unexpected type: %d\n", reply->type);
        return NULL;
    }

    if (reply->elements == 0) {
        return NULL;
    }

    char *element = NULL;
    element = strdup(reply->element[0]->str);

    freeReplyObject(reply);

    return element;
}

void removeFirstElementFromArray(char *key, redisContext *client) {
    redisReply *reply = redisCommand(client, "LPOP %s 1", key);

    if (reply->type == REDIS_REPLY_ERROR) {
        printf("[redis]: error: %s\n", reply->str);
    }

    freeReplyObject(reply);
}

void setHashField(char *key, char *field, char *value, redisContext *client) {
    redisReply *reply = redisCommand(client, "HSET %s %s %s", key, field, value);

    if (reply->type == REDIS_REPLY_ERROR) {
        printf("[redis]: error: %s\n", reply->str);
    }

    freeReplyObject(reply);
}