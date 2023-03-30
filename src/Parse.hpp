#pragma once
#include "Config.hpp"
#include "CSS.hpp"
#include "Helpers.cpp"
#include <iostream>
#include <string.h>

namespace Parse {

void reallocBuilder(char **builder, int times);
    
char **tokenize(char *input, const char *keychars, bool insideBrackets);

} // namespace Parse