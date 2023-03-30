#pragma once
#include "Config.hpp"
#include "Section.cpp"
#include "Selectors.cpp"
#include <iostream>

struct DoubleLinkedList {
    DoubleLinkedList *next = NULL;
    DoubleLinkedList *previous = NULL;
    Section sections[T];
    bool alreadyTaken[T];
    int sizeTaken;
    
    void init() {
        next = NULL;
        previous = NULL;
        sizeTaken = 0;
        for (int i=0; i<T; i++) {
            sections[i].attributes = NULL;
            sections[i].selectors = NULL;
            alreadyTaken[i] = false;
        }
    }
    
    void empty() {
        for (int i=0; i<T; i++) {
            if (!alreadyTaken[i]) continue;
            sections[i].emptySection();
        }
    }
    
    DoubleLinkedList *tail() {
        DoubleLinkedList *temp = this;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        return temp;
    }


    Section *addSection() {
        DoubleLinkedList *temp = this;
        Section *section = NULL;
        bool found = false;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        for (int i = T - 1; i > 0; i--) {
            if (temp->alreadyTaken[i - 1] && !temp->alreadyTaken[i]) {
                section = &(temp->sections[i]);
                return section;
            }
            if (temp->alreadyTaken[i])  { 
            	found = true;
            	break;
            }
        }
        if (!found && temp->alreadyTaken[0] == false && temp->alreadyTaken[1] == false) {
            section = &(temp->sections[0]);
        } else {
            DoubleLinkedList *list = new DoubleLinkedList;
            list->init();
            list->previous = this;
            section = list->addSection();
            append(list);
        }
        return section;
    }
    void append(DoubleLinkedList *element) {
        element->next = NULL;
        DoubleLinkedList *temp = this;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        element->previous = temp;
        temp->next = element;
    }
};