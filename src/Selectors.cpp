#pragma once
#include "Attributes.cpp"
#include "string.h"
#include <iostream>
struct Selectors {
    Selectors *next = NULL;
    Selectors *head = NULL;
    char *name;

    bool checkForDuplicate(char *dupName) {
        Selectors *temp = head;
        bool exists = false;
        while (temp != NULL) {
            if (strcmp(temp->name, dupName) == 0) {
                exists = true;
                break;
            }
            temp = temp->next;
        }
        return exists;
    }
    void append(Selectors *element) {
        element->next = NULL;
        Selectors *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        element->head = head;
        temp->next = element;
    }
};