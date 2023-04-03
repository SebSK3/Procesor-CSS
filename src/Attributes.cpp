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

            delete[] attrib->value;
            delete[] attrib->name;
            delete attrib;
            return newHead;
        }
        while (temp != NULL) {
            if (temp->next == attrib) {
                if (temp->next != NULL) {
                    temp->next = temp->next->next;
                }
                delete[] attrib->name;
                delete[] attrib->value;
                delete attrib;
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
                delete[] temp->value;
                temp->value = attrib->value;
                delete[] attrib->name;
                exists = true;
                break;
            }
            temp = temp->next;
        }
        return exists;
    }
};