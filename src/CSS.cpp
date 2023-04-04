#include "CSS.hpp"
#include "CMD.hpp"

CSS::CSS() {
    cmd = (CMD*)malloc(sizeof(CMD));
    cmd = new (cmd) CMD(this);
    currentSection = NULL;
    insideBlock = false;
    list = new DoubleLinkedList;
    list->init();
    currentList = list;
    currentSection = &(list->sections[0]);
}

CSS::~CSS() {
    DoubleLinkedList *temp = list;
    while (temp != NULL) {
        DoubleLinkedList *deletingList = temp;
        temp->empty();
        temp = temp->next;
        delete deletingList;
    }
    free(cmd);
}

void CSS::SetSectionTaken(Section *section) {
    for (int i = 0; i < T; i++) {
        if (&(currentList->sections[i]) == section) {
            currentList->alreadyTaken[i] = true;
            return;
        }
    }
}

void CSS::Extract(char **tokens, int tokensLength) {
    for (int i = 0; i < tokensLength; i++) {

        switch (*tokens[i]) {
        case '{':
            insideBlock = true;
            free(tokens[i]);
            break;
        case '}':
            free(tokens[i]);
            SetSectionTaken(currentSection);
            currentList->sizeTaken++;
            currentSection = currentList->addSection();
            if (currentList->next != NULL) {
                currentList = currentList->next;
            }
            insideBlock = false;
            break;
        default:
            if (tokens[i + 1] == NULL ||
                (!tokenIsAttribute(tokens, tokensLength, i) && !insideBlock)) {
                /* This is for sure selector */

                /* If there are any attributes in current section (tail), then
                 *  we start building next section
                 */
                if (currentSection->attributes != NULL) {
                    SetSectionTaken(currentSection);
                    list->sizeTaken++;
                    currentSection = list->addSection();
                    // AppendSection();
                }

                Selectors *selector = (Selectors *)malloc(sizeof(Selectors));
                selector->name = tokens[i];

                /* If selector doesn't exist, then this selector is the head */
                if (currentSection->selectors == NULL) {
                    selector->head = selector;
                    selector->next = NULL;
                    currentSection->selectors = selector;
                } else {
                    bool exists = currentSection->selectors->checkForDuplicate(
                        selector->name);
                    if (!exists)
                        currentSection->selectors->append(selector);
                    else {
                        free(selector->name);
                        free(selector);
                    }
                }
            } else if (i + 1 < tokensLength && *tokens[i + 1] == ':') {
                /* It's definietly attribute */
                /* TODO: set as taken when parsing global attributes */
                Attributes *attrib = (Attributes *)malloc(sizeof(Attributes));
                attrib->name = tokens[i];
                attrib->value = tokens[i + 2];
                attrib->next = NULL;
                if (currentSection->attributes == NULL) {
                    attrib->head = attrib;
                    currentSection->attributes = attrib;
                } else {
                    bool exists =
                        currentSection->attributes->checkForDuplicate(attrib);
                    if (!exists)
                        currentSection->attributes->append(attrib);
                    else {
                        free(attrib);
                    }
                }
                /* Skip this attribute */
                if (i + 2 < tokensLength)
                    free(tokens[i + 1]);
                i = i + 2;
                if (i + 1 < (tokensLength) && *tokens[i + 1] == ';') {
                    free(tokens[i + 1]);
                    i++;
                }

                break;
            } else {
                free(tokens[i]);
            }
        }
    }
#ifdef DEBUG
    std::cout << "[ok] TOKENS EXTRACTED SUCCESSFULLY" << std::endl;
#endif
}

void appendToLine(char **line, char c, int lineAllocs, int &index) {
    if (index >= MAX_DEFAULT_LENGTH - 2) {
        *line = (char *)realloc(*line, sizeof(char) *
                                           (MAX_DEFAULT_LENGTH * lineAllocs));
    }

    (*line)[index] = c;
    index++;
}

void CSS::ParseInput(char *line, bool &CSSMODE) {
    if (strcmp(line, "????") == 0) {
        CSSMODE = false;
        return;
    }
    if (strcmp(line, "****") == 0) {
        CSSMODE = true;
        return;
    }
    if (CSSMODE) {
        ParseCSS(line);
    } else {
        cmd->Execute(line);
    }
}

void CSS::GetInput() {
    char *line = (char *)malloc(sizeof(char) * MAX_DEFAULT_LENGTH);
    bool CSSMODE = true;
    int lineAllocs = 1;
    char c;
    int i = 0;

    while ((c = getchar()) != EOF) {
        if (c != '\n' && c != EOF) {

            if ((c > 10 || c < 10) && c < ' ') continue;
            appendToLine(&line, c, lineAllocs, i);
            continue;
        }
        line[i] = '\0';
        if (i == 0)
            continue;

        i = 0;
        ParseInput(line, CSSMODE);
    }
    if (i > 0) {
        line[i] = '\0';
        ParseInput(line, CSSMODE);
    }
    free(line);
}

void CSS::ParseCSS(char *input) {

    const char *keychars = "{};";
    char **tokenized = Parse::tokenize(input, keychars, insideBlock);

#ifdef DEBUG
    DUMP_ALL_TOKENS(tokenized);
#endif
    int i = 0;
    while (tokenized[i] != NULL) {
        i++;
    }

    Extract(tokenized, i);
    free(tokenized);
#ifdef DEBUG
    DUMP_ALL_SECTIONS(list);
#endif
}