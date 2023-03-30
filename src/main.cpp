// Disable "C style pointer casting"
#pragma warning(push)
#pragma warning(disable : 4363)
#include "CSS.hpp"


int main() {
    /* Use new instead of malloc, just so constructor will be called */
    CSS *css = new CSS();
    css->GetInput();
    delete css;
    return 0;
}