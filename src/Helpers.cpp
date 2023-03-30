#pragma once
#include "Attributes.cpp"
#include "Config.hpp"
#include "Section.cpp"
#include "Selectors.cpp"
#include "DoubleLinkedList.cpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Wzorowanie na:
 * https://stackoverflow.com/questions/352055/best-algorithm-to-strip-leading-and-trailing-spaces-in-c
 */
inline char *strstrip(char *s) {
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}

inline bool isInside(char c, const char *arr) {
    for (unsigned int i = 0; i < strlen(arr); i++) {
        if (c == arr[i]) {
            return true;
        }
    }
    return false;
}

inline char *buildString(char *builder, int &length) {
    builder[length] = '\0';
    char *stripped = strstrip(builder);
    char *temp = (char *)malloc(sizeof(char) * (strlen(stripped) + 1));
    strcpy(temp, stripped);
    length = 0;
    return temp;
}

inline void appendToResult(char ***result, char *string, int &resultSize) {
    if (strlen(string) == 0) {
        return;
    }
    *result = (char **)realloc(*result, sizeof(char *) * (resultSize + 2));
    if (result == NULL) {
        exit(-1);
    }
    (*result)[resultSize] = string;
    (*result)[resultSize + 1] = NULL;
    resultSize++;
}

inline bool tokenIsAttribute(char **tokens, int length, int i) {
    while (i < length) {
        if (*tokens[i] == ';') {
            return true;
        }
        if (*tokens[i] == '{') {
            return false;
        }
        i++;
    }
    return false;
}

inline char *SelectorName(char *in1, char *in2, char *in3) {
    char *out = (char *)malloc(sizeof(char) *
                               (strlen(in1) + strlen(in2) + strlen(in3) + 1));
    strcpy(out, in1);
    strcat(out, in2);
    strcat(out, in3);
    free(in1);
    free(in2);
    free(in3);
    return out;
}

inline char *AppendSelectorName(char *selectorName, char *in1, char *in2) {
    char *out = (char *)malloc(
        sizeof(char) * (strlen(selectorName) + strlen(in1) + strlen(in2) + 1));
    strcpy(out, selectorName);
    strcat(out, in1);
    strcat(out, in2);
    free(selectorName);
    free(in1);
    free(in2);
    return out;
}

inline char *buildSelectorName(char **tokens, int tokensLength, int &i) {
    char *name = NULL;

    bool foundColon = false;
    /* Check if it's selector with ':', then build whole selector */
    if (i + 2 < tokensLength && (*tokens[i] == ':' || *tokens[i + 1] == ':'))
        while (i + 2 < tokensLength && *tokens[i + 1] == ':') {

            if (name != NULL) {
                i++;
                name = AppendSelectorName(name, tokens[i], tokens[i + 1]);
                i = i + 1;
            } else {
                name = SelectorName(tokens[i], tokens[i + 1], tokens[i + 2]);
                i = i + 2;
            }
            foundColon = true;
        }
    if (!foundColon) {
        name = tokens[i];
    }
    return name;
}

inline void FreeTokens(char **tokens) {
    int i=0;
    while (tokens[i] != NULL) {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

#ifdef DEBUG
inline void DUMP_ALL_TOKENS(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        std::cout << "[" << tokens[i] << "], ";
        i++;
    }
    std::cout << std::endl;
}

inline void DUMP_ALL_SECTIONS(DoubleLinkedList *list) {
    if (list == NULL) {
        return;
    }
    while (list != NULL) {
        for (int i = 0; i < T; i++) {
            if (!list->alreadyTaken[i])
                continue;
            Selectors *tempSelector = list->sections[i].selectors;
            std::cout << "SECTION NUMBER: " << i << std::endl;
            std::cout << "SELECTIONS: " << std::endl;
            while (tempSelector != NULL) {
                std::cout << '[' << tempSelector->name << "], ";
                tempSelector = tempSelector->next;
            }
            std::cout << std::endl;
            std::cout << "ATTRIBUTES:" << std::endl;
            Attributes *tempAttrib = list->sections[i].attributes;
            while (tempAttrib != NULL) {
                std::cout << tempAttrib->name << " :: " << tempAttrib->value
                          << std::endl;
                tempAttrib = tempAttrib->next;
            }
        }
        list = list->next;
    }
}
#endif
