#pragma once
#include "string.h"
#include <iostream>
struct Attributes {
    Attributes *next = NULL;
    Attributes *head = NULL;
    char *name;
    char *value;
    const void append(Attributes *element) {
        element->next = NULL;
        Attributes *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        element->head = head;
        temp->next = element;
    }
    Attributes *deleteAttrib(Attributes *attrib) {
        Attributes *temp = head;
        if (temp == attrib) {
            Attributes *newHead = head->next;
            while (temp != NULL) {
                temp->head = newHead;
                temp = temp->next;
            }

            free(attrib->value);
            free(attrib->name);
            free(attrib);
            return newHead;
        }
        while (temp != NULL) {
            if (temp->next == attrib) {
                if (temp->next != NULL) {
                    temp->next = temp->next->next;
                }
                free(attrib->name);
                free(attrib->value);
                free(attrib);
                return head;
            }
            temp = temp->next;
        }
        return head;
    }

    const bool checkForDuplicate(Attributes *attrib) {
        Attributes *temp = head;
        bool exists = false;
        while (temp != NULL) {
            if (strcmp(temp->name, attrib->name) == 0) {
                free(temp->value);
                temp->value = attrib->value;
                free(attrib->name);
                exists = true;
                break;
            }
            temp = temp->next;
        }
        return exists;
    }
};