//
// Created by stefan on 20/03/24.
//

#ifndef CALCULATORAADS_STRING_H
#define CALCULATORAADS_STRING_H

#include <cstdio>

namespace data_structures {

    class String {
    public:
        String(const String &other);


        explicit String(const char c);

        explicit String(const char *s = nullptr);

        ~String() {
            delete[] str;
        }

        String& operator=(const String &other);

        size_t size() const;

        String operator+(const String &other) const;

        String operator+(int number) const;

        const char *c_str() const;

    private:
        String(size_t n);
        char *str;
    };

} // data_structures


#endif //CALCULATORAADS_STRING_H
