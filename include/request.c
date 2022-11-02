//
// Created by David Casey on 11/1/22.
//

#include <stdlib.h>
#include <jsmn.h>
#include <string.h>
#include "request.h"
#include "data-store.h"
#include "string-util.h"

char *getTokenValue(char *json, struct jsmntok token) {
    return substring(json, token.start + 1, token.end - token.start);
}

Request *parseRequestFromJson(char *json) {
    int maxTokens = 5;
    Request *request = malloc(sizeof(Request));

    jsmn_parser parser;
    jsmntok_t tokens[maxTokens];

    jsmn_init(&parser);
    jsmn_parse(&parser, json, strlen(json), tokens, maxTokens);

    int i = 0;
    while (i < maxTokens - 1 && tokens[i].type != JSMN_UNDEFINED) {
        if (tokens[i].type == JSMN_STRING) {
            char *value = getTokenValue(json, tokens[i]);

            if (strcmp(value, "action") == 0) {
                request->action = getTokenValue(json, tokens[i + 1]);
            } else if (strcmp(value, "value") == 0) {
                request->value = atoi(getTokenValue(json, tokens[i + 1]));
            }
        }
        i++;
    }

    return request;
}

Request *getRequest(redisContext *client) {
    char *requestJson = getFirstElementFromArray("requests", client);
    if (requestJson == NULL) {
        return NULL;
    }

    return parseRequestFromJson(requestJson);
}

void removeRequest(redisContext *client) {
    removeFirstElementFromArray("requests", client);
}