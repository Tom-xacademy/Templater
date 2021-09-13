#include <iostream>
#include <string>
#include "InputHandler.h"

using Text = std::string;
using int32 = int;

EInputStatus InputHandler::Validate(Text word) const {
    int32 length = word.length();
    
    if (length <= 1) return EInputStatus::EMPTY_STRING;

    if (word[length -1] == 's') return EInputStatus::ENDS_WITH_S;

    if (length > 10) return EInputStatus::TOO_LONG;

    return EInputStatus::OK;
}

Text InputHandler::Convert(Text word) const {
    for (auto letter: word) {
        letter = tolower(letter);
    }
    return word;
}