#include "Parse.hpp"

void Parse::reallocBuilder(char **builder, int times) {
    *builder = (char*)realloc(*builder, sizeof(char) * (times));
    if (builder == NULL) {
        exit(-1);
    }
}

char **Parse::tokenize(char *input, const char *keychars, bool insideBrackets) {
    if (strlen(input) == 0) {
        return NULL;
    }
    char **result = (char **)malloc(sizeof(char *));
    result[0] = NULL;

    int resultSize = 0;
    int builderAllocs = 1;

    char *builder = (char *)malloc(sizeof(char) * MAX_DEFAULT_LENGTH + 1);

    int builderIndex = 0;
    char *token;

    for (unsigned int charIndex = 0; charIndex < strlen(input); charIndex++) {
        bool isDelimiter = isInside(input[charIndex], delimiters);
        bool isKeychar = isInside(input[charIndex], keychars);

        if (isKeychar) {
            /*  If builderIndex > 0, then there is still word
             *   in builder buffer, so
             *   append it to result
             */
            if (builderIndex > 0) {
                token = buildString(builder, builderIndex);
                if (strlen(token) > 0)
                    appendToResult(&result, token, resultSize);
                else free(token);
            }
            /* Append keychar to result */
            builder[builderIndex] = input[charIndex];
            builderIndex++;
            token = buildString(builder, builderIndex);
            appendToResult(&result, token, resultSize);
            switch (*token) {
                case '{':
                    insideBrackets = true;
                    break;
                case '}':
                    insideBrackets = false;
                    break;
            }
            /*  If it was ':', check if it's actually attribute,
             *   if so, it can be long string with spaces and commas,
             *   get it whole and append
             */
            if (*token == ':' && insideBrackets) {
                /* Skip the ':' */
                charIndex++;
                while (charIndex < strlen(input) && input[charIndex] != ';' &&
                       input[charIndex] != '}') {
                    builder[builderIndex] = input[charIndex];
                    builderIndex++;
                    charIndex++;
                }
                charIndex--;
            }
            continue;
        }
        if (isDelimiter) {
            token = buildString(builder, builderIndex);
            appendToResult(&result, token, resultSize);
            continue;
        }
        if (builderIndex >= (MAX_DEFAULT_LENGTH * builderAllocs)-1) {
            reallocBuilder(&builder, builderAllocs);
        }
        if (builderIndex < MAX_DEFAULT_LENGTH * builderAllocs) {
            builder[builderIndex] = input[charIndex];
        } else {
            exit(-1);
        }
        builderIndex++;
    }
    /* Something is still in builder, append it */
    if (builderIndex > 0) {
        token = buildString(builder, builderIndex);
        if (strlen(token) == 0) {
            free(token);
        } else {
        appendToResult(&result, token, resultSize);
        }
    }
    free(builder);
    return result;
}

