#include <stdlib.h>
#include <string.h>
#include "include/request.h"
#include "include/data-store.h"
#include "include/gpio.h"

void handleRequest(redisContext *client, Request *request);

int main() {
    redisContext *client;

    initializeGpio();
    client = getDataStoreClient();

    while (1) {
        Request *request = getRequest(client);

        if (request != NULL) {
            handleRequest(client, request);
            removeRequest(client);
        }
    }

    terminateGpio();
    redisFree(client);
    exit(EXIT_SUCCESS);
}

void handleRaiseFlagRequest(redisContext *client) {
    printf("[controller]: raising flag.\n");

    if(readInput(GPIO_UPPER_LIMIT) == 1) {
        enableOutput(GPIO_RAISE_FLAG);
        while (readInput(GPIO_UPPER_LIMIT) == 1);
        disableOutput(GPIO_RAISE_FLAG);
    }

    setHashField("status", "flag", "RAISED", client);
    printf("[controller]: raised flag.\n");
}

void handleHalfFlagRequest(redisContext *client) {
    printf("[controller]: half masting flag.\n");
    setHashField("status", "flag", "HALF", client);
    printf("[controller]: half masted flag.\n");
}

void handleLowerFlagRequest(redisContext *client) {
    printf("[controller]: lowering flag.\n");

    if(readInput(GPIO_LOWER_LIMIT) == 1) {
        enableOutput(GPIO_LOWER_FLAG);
        while (readInput(GPIO_LOWER_LIMIT) == 1);
        disableOutput(GPIO_LOWER_FLAG);
    }

    setHashField("status", "flag", "LOWERED", client);
    printf("[controller]: lowered flag.\n");
}

void handleLightsRequest(redisContext *client, Request *request) {
    printf("[controller]: setting lights to (%d).\n", request->value);

    if (request->value == 1) {
        enableOutput(GPIO_ENABLE_LIGHTS);
        setHashField("status", "lights", "ON", client);
    } else {
        disableOutput(GPIO_ENABLE_LIGHTS);
        setHashField("status", "lights", "OFF", client);
    }

    printf("[controller]: lights set to (%d).\n", request->value);
}

void handleRequest(redisContext *client, Request *request) {
    printf("[controller]: servicing request with action (%s).\n", request->action);

    if (strcmp(request->action, "RAISE") == 0) {
        handleRaiseFlagRequest(client);
    } else if (strcmp(request->action, "HALF") == 0) {
        handleHalfFlagRequest(client);
    } else if (strcmp(request->action, "LOWER") == 0) {
        handleLowerFlagRequest(client);
    } else if (strcmp(request->action, "LIGHTS") == 0) {
        handleLightsRequest(client, request);
    } else {
        printf("[controller]: unsupported request action (%s).", request->action);
        exit(EXIT_FAILURE);
    }

    free(request);
}