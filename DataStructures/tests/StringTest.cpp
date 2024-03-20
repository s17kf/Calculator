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