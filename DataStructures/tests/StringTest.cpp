//strncpy
// Created by stefan on 20/03/24.
//

#include "gtest/gtest.h"

#include <cstring>
#include "String.h"

using data_structures::String;

class StringTest : public ::testing::Test {
protected:
};

TEST_F(StringTest, emptyString) {
    String s;
    ASSERT_EQ(0, s.size());
    ASSERT_EQ('\0', s.c_str()[0]);
}

TEST_F(StringTest, oneCharString) {
    String s('f');
    ASSERT_EQ(1, s.size());
    ASSERT_EQ('f', s.c_str()[0]);
}

TEST_F(StringTest, stringTest) {
    const char testString[] = "Test string";
    String s(testString);
    ASSERT_EQ(strlen(testString), s.size());
    ASSERT_EQ(0, std::strcmp(testString, s.c_str()));
}

TEST_F(StringTest, stringConcatenation) {
    const String s1("Part 1");
    const String s2 = String("Part 2");
    const char expectedResult[] = "Part 1Part 2";
    String result = s1 + s2;

    const size_t expectedSize = s1.size() + s2.size();
    ASSERT_EQ(expectedSize, result.size());
    ASSERT_EQ(0, std::strcmp(expectedResult, result.c_str()));
}

TEST_F(StringTest, stringSelfConcatenation) {
    String s1("text");
    const String s2 = String("other");
    const char expectedResult[] = "textother";
    const size_t expectedSize = s1.size() + s2.size();
    s1 += s2;
    ASSERT_EQ(expectedSize, s1.size());
    ASSERT_EQ(0, std::strcmp(expectedResult, s1.c_str()));
}

TEST_F(StringTest, stringSelfConcatenationWithCapacityInitialization) {
    String testedString((size_t)50);
    const String s1("text");
    const String s2 = String("other");
    const char expectedResult[] = "textother";
    const size_t expectedSize = s1.size() + s2.size();
    testedString += s1;
    ASSERT_EQ(s1.size(), testedString.size());
    ASSERT_EQ(0, std::strcmp(s1.c_str(), testedString.c_str()));
    testedString += s2;
    ASSERT_EQ(expectedSize, testedString.size());
    ASSERT_EQ(0, std::strcmp(expectedResult, testedString.c_str()));
}

TEST_F(StringTest, stringAndNumberConcatenation) {
    const String s("str");
    const int oneDigitNumber = 5;
    const int twoDigitNumber = 24;
    const char expectedOneDigitResult[] = "str5";
    const char expectedTwoDigitResult[] = "str24";

    String oneDigitResult = s + oneDigitNumber;
    String twoDigitResult = s + twoDigitNumber;

    ASSERT_EQ(4, oneDigitResult.size());
    ASSERT_EQ(0, std::strcmp(expectedOneDigitResult, oneDigitResult.c_str()));
    ASSERT_EQ(0, std::strcmp(expectedTwoDigitResult, twoDigitResult.c_str()));
    ASSERT_EQ(5, twoDigitResult.size());
}
