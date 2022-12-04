#include <stdlib.h>
#include <string.h>
#include "include/request.h"
#include "include/data-store.h"
#include "include/gpio.h"

/**
 * Handles a request by distributing it to the correct request handler.
 * @param client The data store client.
 * @param request The request to handle.
 */
void handleRequest(redisContext *client, Request *request);

int main() {
    redisContext *client;

    initializeGpio();
    client = getDataStoreClient();

    while (1) {
        // Continually loop and service requests.
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

// Handles a request to raise the flag by enabling the raise output until the upper limit input is triggered.
void handleRaiseFlagRequest(redisContext *client) {
    printf("[controller]: raising flag.\n");

    if (readInput(GPIO_UPPER_LIMIT) == 1) {
        enableOutput(GPIO_RAISE_FLAG);
        while (readInput(GPIO_UPPER_LIMIT) == 1);
        disableOutput(GPIO_RAISE_FLAG);
    }

    setHashField("status", "flag", "RAISED", client);
    printf("[controller]: raised flag.\n");
}

// Handles a request to half-staff the flag. TODO: Implement logic to determine how long the motor should run.
void handleHalfFlagRequest(redisContext *client) {
    printf("[controller]: half masting flag.\n");
    setHashField("status", "flag", "HALF", client);
    printf("[controller]: half masted flag.\n");
}

// Handles a request to lower the flag by enabling the lower output until the lower limit input is triggered.
void handleLowerFlagRequest(redisContext *client) {
    printf("[controller]: lowering flag.\n");

    if (readInput(GPIO_LOWER_LIMIT) == 1) {
        enableOutput(GPIO_LOWER_FLAG);
        while (readInput(GPIO_LOWER_LIMIT) == 1);
        disableOutput(GPIO_LOWER_FLAG);
    }

    setHashField("status", "flag", "LOWERED", client);
    printf("[controller]: lowered flag.\n");
}

// Handles a lights request, either enabling or disabling the lights depending on the request value.
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