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
            delete[] deletingSelector->name;
            delete[] deletingSelector;
        }
        Attributes *tempAttribute = attributes;
        while (tempAttribute != NULL) {
            Attributes *deletingAttribute;
            deletingAttribute = tempAttribute;
            tempAttribute = tempAttribute->next;
            delete[] deletingAttribute->value;
            delete[] deletingAttribute->name;
            delete deletingAttribute;
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