#include "CSS.hpp"


int main() {
    CSS *css = (CSS*)malloc(sizeof(CSS));
    css->Init();
    css->GetInput();
    css->~CSS();
    free(css);
    return 0;
}