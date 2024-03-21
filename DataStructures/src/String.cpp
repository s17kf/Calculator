//
// Created by stefan on 20/03/24.
//

#include "String.h"

#include <charconv>

namespace data_structures {

    String::String(const String &other) {
        str = new char[strlen(other.str) + 1];
        strncpy(str, other.str, strlen(other.str) + 1);
    }

    String::String(const char c) {
        str = new char [2] {c, '\0'};
    }

    String::String(const char *s) {
        if (s == nullptr) {
            str = new char[1];
            str[0] = '\0';
            return;
        }
        const size_t charactersToCopy = strlen(s);
        str = new char[charactersToCopy + 1];
        str[charactersToCopy] = '\0';
        strncpy(str, s, charactersToCopy);
    }

    String::String(size_t n) {
        str = new char[n];
    }

    String &String::operator=(const String &other) {
        if (this == &other)
            return *this;
        delete[] str;
        str = new char [other.size() + 1];
        strncpy(str, other.str, other.size()+1);
        return *this;
    }

    String String::operator+(const String &other) const {
        String result(size() + other.size() + 1);
        strncpy(result.str, str ,size());
        strncpy(&result.str[size()], other.str, other.size() + 1);
        return result;
    }

    String String::operator+(int number) const {
        char numberStr[8] = {};
        std::to_chars(numberStr, numberStr + 8, number);
        String result(size() + strlen(numberStr) + 1);
        strncpy(result.str, str ,size());

        strncpy(&result.str[size()], numberStr, strlen(numberStr) + 1);
        return result;
    }

} // data_structures