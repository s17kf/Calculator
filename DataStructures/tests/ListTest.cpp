//
// Created by stefan on 12/03/24.
//

#include <memory>
#include "gtest/gtest.h"

#include "List.h"

using data_structures::List;

class ListTest : public ::testing::Test {
protected:
    std::unique_ptr<List<int>> list;

    void SetUp() override {
        list = std::make_unique<List<int>>();
    }

    void TearDown() override {
        list.reset();
    }
};

TEST_F(ListTest, emptyListTest) {
    ASSERT_EQ(0, list->size());
}

TEST_F(ListTest, rangeBasedLoopOverEmptyList) {
    size_t loopCounter = 0;
    for (const auto& el : *list) {
        ++loopCounter;
    }
    ASSERT_EQ(0, loopCounter);
}


