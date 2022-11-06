//
// Created by David Casey on 11/1/22.
//

#include <malloc.h>
#include <stddef.h>
#include <stdlib.h>
#include "string-util.h"

char *substring(char *string, int position, int length) {
    char *substringPtr;
    int charIndex;

    substringPtr = malloc(length + 1);

    if (substringPtr == NULL) {
        printf("[substringPtr] unable to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    for (charIndex = 0; charIndex < length; charIndex++) {
        *(substringPtr + charIndex) = *(string + position - 1);
        string++;
    }

    *(substringPtr + charIndex) = '\0';

    return substringPtr;
}