#pragma once
#include "Selectors.cpp"
#include <iostream>

struct Section {
    Selectors *selectors = NULL;
    Attributes *attributes = NULL;
    void emptySection() {
        Selectors *tempSelector = selectors;
        while (tempSelector != NULL) {
            Selectors *deletingSelector = tempSelector;
            tempSelector = tempSelector->next;
            free(deletingSelector->name);
            free(deletingSelector);
        }
        Attributes *tempAttribute = attributes;
        while (tempAttribute != NULL) {
            Attributes *deletingAttribute;
            deletingAttribute = tempAttribute;
            tempAttribute = tempAttribute->next;
            free(deletingAttribute->value);
            free(deletingAttribute->name);
            free(deletingAttribute);
        }
        attributes = NULL;
        selectors = NULL;
    }
    Selectors *getNthSelector(int n) {
        Selectors *selector = selectors;
        int i = 0;
        if (i == n) {
            return selector;
        }
        while (selector != NULL) {
            selector = selector->next;
            i++;
            if (i == n) {
                return selector;
            }
        }
        return NULL;
    }


    
};