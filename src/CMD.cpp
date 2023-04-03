#include "CMD.hpp"
#include "CSS.hpp"

void CMD::Init(CSS *cssIn) {
    css = cssIn;
}

const void CMD::CMD_QUESTIONMARK(char *input) {

    int count = 0;
    DoubleLinkedList *tempList = css->list;
    while (tempList != NULL) {
        count += tempList->sizeTaken;
        tempList = tempList->next;
    }
    std::cout << input << " == ";
    std::cout << count << std::endl;
}
void CMD::S(char *input, char **tokens) {
    if (isdigit(*tokens[0])) {
        int whichSection;
        sscanf(tokens[0], "%d", &whichSection);
        Section *section = GetNthSection(whichSection - 1);
        if (section == NULL) {
            return;
        }
        if (*tokens[2] == '?') {
            int count = 0;
            Selectors *selector = section->selectors;
            while (selector != NULL) {
                selector = selector->next;
                count++;
            }
            std::cout << input << " == ";
            std::cout << count << std::endl;
            return;
        } else if (isdigit(*tokens[2])) {

            int whichSelector;
            sscanf(tokens[2], "%d", &whichSelector);
            Selectors *selector = section->getNthSelector(whichSelector - 1);
            if (selector != NULL) {
                std::cout << input << " == ";
                std::cout << selector->name << std::endl;
            }
            return;
        }
    } else {
        int count = 0;

        DoubleLinkedList *tempList = css->list;
        while (tempList != NULL) {
            for (int i = 0; i < T; i++) {
                if (!tempList->alreadyTaken[i])
                    continue;

                Selectors *selector = tempList->sections[i].selectors;
                while (selector != NULL) {
                    if (strcmp(selector->name, tokens[0]) == 0) {
                        count++;
                    }
                    selector = selector->next;
                }
            }
            tempList = tempList->next;
        }
        std::cout << input << " == ";
        std::cout << count << std::endl;
    }
}

void CMD::A(char *input, char **tokens) {

    if (isdigit(*tokens[0])) {
        int whichSection;
        sscanf(tokens[0], "%d", &whichSection);
        Section *section = GetNthSection(whichSection - 1);
        if (section == NULL) {
            return;
        }
        if (*tokens[2] == '?') {
            Attributes *attrib = section->attributes;
            int count = 0;
            while (attrib != NULL) {
                attrib = attrib->next;
                count++;
            }

            std::cout << input << " == ";
            std::cout << count << std::endl;
        } else {
            Attributes *attrib = section->attributes;
            while (attrib != NULL) {
                if (strcmp(attrib->name, tokens[2]) == 0) {

                    std::cout << input << " == ";
                    std::cout << attrib->value << std::endl;
                    return;
                }
                attrib = attrib->next;
            }
        }
        return;
    } else {

        int count = 0;
        DoubleLinkedList *tempList = css->list;
        while (tempList != NULL) {
            for (int i = 0; i < T; i++) {
                if (!tempList->alreadyTaken[i])
                    continue;

                Attributes *attrib = tempList->sections[i].attributes;
                while (attrib != NULL) {
                    if (strcmp(attrib->name, tokens[0]) == 0) {
                        count++;
                    }
                    attrib = attrib->next;
                }
            }
            tempList = tempList->next;
        }
        std::cout << input << " == ";
        std::cout << count << std::endl;
    }
}

void CMD::E(char *input, char **tokens) {
    DoubleLinkedList *tempList = css->list->tail();
    while (tempList != NULL) {
        for (int i = T - 1; i >= 0; i--) {
            if (!tempList->alreadyTaken[i])
                continue;
            Selectors *selector = tempList->sections[i].selectors;
            while (selector != NULL) {
                if (strcmp(selector->name, tokens[0]) == 0) {
                    Attributes *attrib = tempList->sections[i].attributes;
                    while (attrib != NULL) {
                        if (strcmp(attrib->name, tokens[2]) == 0) {

                            std::cout << input << " == ";
                            std::cout << attrib->value << std::endl;
                            return;
                        }
                        attrib = attrib->next;
                    }
                }
                selector = selector->next;
            }
        }
        tempList = tempList->previous;
    }
}

Section *CMD::GetNthSection(int n) {
    int i = 0;
    DoubleLinkedList *tempList = css->list;
    while (tempList != NULL) {
        if (n > (i + (tempList->sizeTaken))) {
            i = i + tempList->sizeTaken;
            tempList = tempList->next;
            continue;
        }
        for (int j = 0; j < T; j++) {

            if (tempList->alreadyTaken[j]) {
                if (i == n)
                    return &(tempList->sections[j]);

                i++;
            }
        }
        tempList = tempList->next;
    }
    return NULL;
}

DoubleLinkedList *CMD::RemoveEmptySection(int n) {
    int i = 0;
    DoubleLinkedList *tempList = css->list;
    while (tempList != NULL) {
        for (int j = 0; j < T; j++) {

            if (tempList->alreadyTaken[j]) {
                if (i == n) {
                    tempList->sections[j].emptySection();
                    tempList->alreadyTaken[j] = false;
                    tempList->sizeTaken--;
                    return tempList;
                }

                i++;
            }
        }
        tempList = tempList->next;
    }
    return NULL;
}

bool CMD::DeleteNthSection(int n) {
    int i = 0;
    DoubleLinkedList *tempList = css->list;
    while (tempList != NULL) {
        if (n > (i + tempList->sizeTaken)) {
            i = i + tempList->sizeTaken;
            tempList = tempList->next;
            continue;
        }
        for (int j = 0; j < T; j++) {

            if (tempList->alreadyTaken[j]) {
                if (i == n) {

                    tempList->sections[j].emptySection();
                    tempList->alreadyTaken[j] = false;
                    tempList->sizeTaken--;
                    CheckForDeletion(tempList);
                    return true;
                }
                i++;
            }
        }
        tempList = tempList->next;
    }
    return false;
}

void CMD::CheckForDeletion(DoubleLinkedList *list) {
    if (list != NULL)
    if (list->sizeTaken == 0) {
        for (int i=0; i<T; i++) {
            if (css->currentSection == &(list->sections[i])) {
                return;
            }
        }
        if (list->previous == NULL && list->next != NULL) {
            css->list = list->next;
            css->list->previous = NULL;
            list->empty();
            free(list);
        } else if (list->next == NULL && list->previous != NULL) {
            list->previous->next = NULL;
            list->empty();
            free(list);
        } else if (list->previous != NULL && list->next != NULL) {
            list->previous->next = list->next;
            list->next->previous = list->previous;
            list->empty();
            free(list);
        }
    }
}
void CMD::D(char *input, char **tokens) {
    int whichSection = -1;
    sscanf(tokens[0], "%d", &whichSection);

    if (*tokens[2] == '*') {
        if (DeleteNthSection(whichSection - 1)) {
            std::cout << input << " == ";
            std::cout << "deleted" << std::endl;
        }
    } else {

        Section *section = GetNthSection(whichSection - 1);
        if (section == NULL) {
            return;
        }
        Attributes *attrib = section->attributes;
        while (attrib != NULL) {
            if (strcmp(attrib->name, tokens[2]) == 0) {
                attrib = section->attributes->deleteAttrib(attrib);
                section->attributes = attrib;
                std::cout << input << " == ";
                std::cout << "deleted" << std::endl;
                break;
            }
            attrib = attrib->next;
        }
        int count = 0;
        attrib = section->attributes;
        while (attrib != NULL) {
            count++;
            attrib = attrib->next;
        }
        if (count == 0) {
            DoubleLinkedList *list = RemoveEmptySection(whichSection - 1);
            CheckForDeletion(list);
        }
    }
}

void CMD::Execute(char *input) {
    const char *keychars = "{};";
    char **tokenized = Parse::tokenize(input, keychars, false);
#ifdef DEBUG
    DUMP_ALL_TOKENS(tokenized);
#endif
    int i = 0;
    while (tokenized[i] != NULL) {
        i++;
    }
    if (tokenized[0] == NULL) {
        FreeTokens(tokenized);
        return;
    }
    if (tokenized[0][0] == '?') {
        CMD_QUESTIONMARK(input);
#ifdef DEBUG
        DUMP_ALL_SECTIONS(css->list);
#endif
        FreeTokens(tokenized);
        
        return;
    }

    if (i < 2 || i > 3) { 
        FreeTokens(tokenized);
        return;
    }

    switch (*tokenized[1]) {
    case 'S':
        S(input, tokenized);
        break;
    case 'A':
        A(input, tokenized);
        break;
    case 'D':
        D(input, tokenized);
        break;
    case 'E':
        E(input, tokenized);
        break;
    }
#ifdef DEBUG
    DUMP_ALL_TOKENS(tokenized);
#endif
    FreeTokens(tokenized);
}