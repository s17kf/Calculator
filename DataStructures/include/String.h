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

        explicit String(size_t n);

        explicit String(char c);

        explicit String(const char *s = nullptr);

        ~String() {
            delete[] mStr;
        }

        String &operator=(const String &other);

        [[nodiscard]] constexpr size_t size() const { return mSize; }

        String operator+(const String &other) const;

        String operator+=(const String &other);

        String operator+(int number) const;

        String operator+=(int number);

        [[nodiscard]] constexpr const char *c_str() const { return mStr; }

        [[nodiscard]] constexpr char operator[](unsigned int index) {
            return mStr[index];
        }

        void rstrip();

    private:
        size_t mSize;
        size_t mCapacity;
        char *mStr;
    };

} // data_structures


#endif //CALCULATORAADS_STRING_H
