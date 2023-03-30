#pragma once
#include "Attributes.cpp"
#include "Helpers.cpp"
#include "DoubleLinkedList.cpp"
#include "Parse.hpp"
#include "Section.cpp"
#include "Selectors.cpp"
#include <cassert>
#include <string.h>

class CMD;

class CSS {

  public:
    CSS();
    ~CSS();
    void GetInput();
    Section *currentSection;
    DoubleLinkedList *list;
    DoubleLinkedList *currentList;
    //int listSize;

  private:
    bool insideBlock;
    CMD *cmd;
    void SetSectionTaken(Section *section);
    void ParseInput(char *line, bool &CSSMODE);
    void CheckForExistingSection(Section *section);
    void ParseCSS(char *input);
    void Extract(char **tokens, int tokensLength);
    void DeleteSection(Section *section);
    Section *GetNthSection(int n);
};