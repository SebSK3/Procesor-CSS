#include "CSS.hpp"


int main() {
    /* Use new instead of malloc, just so constructor will be called */
    CSS *css = new CSS();
    css->GetInput();
    delete css;
    return 0;
}