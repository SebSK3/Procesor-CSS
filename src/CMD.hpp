#pragma once
#include "Parse.hpp"
#include "DoubleLinkedList.cpp"
#include "Section.cpp"
#include <iostream>
#include <string.h>

class CSS;

class CMD {
  public:
    explicit CMD(CSS* cssIn);
    void Execute(char *input);

  private:
    CSS *css;
    const void CMD_QUESTIONMARK(char *input);
    void CheckForDeletion(DoubleLinkedList *list);
    void D(char *input, char **tokens);
    Section *GetNthSection(int n);
    DoubleLinkedList *RemoveEmptySection(int n);
    void E(char *input, char **tokens);
    bool DeleteNthSection(int n);
    void A(char *input, char **tokens);
    void S(char *input, char **tokens);
};