#include "CSS.hpp"


int main() {
    CSS *css = (CSS*)malloc(sizeof(CSS));
    css = new (css) CSS();
    css->GetInput();
    css->~CSS();
    free(css);
    return 0;
}