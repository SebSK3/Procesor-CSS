#include "CSS.hpp"


int main() {
    void *cssPtr = (CSS*)malloc(sizeof(CSS));
    CSS *css = new (cssPtr) CSS();
    css->GetInput();
    css->~CSS();
    free(cssPtr);
    return 0;
}