//
// Created by stefan on 20/03/24.
//

#ifndef CALCULATORAADS_STRING_H
#define CALCULATORAADS_STRING_H

#include <cstdio>
#include <cstring>

namespace data_structures {

    class String {
    public:
        String(const String &other);

        explicit String(char c);

        explicit String(const char *s = nullptr);

        ~String() {
            delete[] str;
        }

        String &operator=(const String &other);

        [[nodiscard]] size_t size() const { return strlen(str); }

        String operator+(const String &other) const;

        String operator+(int number) const;

        [[nodiscard]] constexpr const char *c_str() const { return str; }

        [[nodiscard]] constexpr char operator[](unsigned int index) {
            return str[index];
        }

    private:
        explicit String(size_t n);

        char *str;
    };

} // data_structures


#endif //CALCULATORAADS_STRING_H
