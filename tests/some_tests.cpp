//
// Created by Jan Woźniak on 20-Mar-20.
//

#include "gtest/gtest.h"

#include <memory>

struct Divider {
    double calc(const double val1, const double val2) {
        return val1 / val2;
    }
};

class SomeFixture : public ::testing::Test {
public:
    SomeFixture() : mSome_value(5), mDivider(std::make_unique<Divider>()) {}

protected:
    uint32_t mSome_value;
    std::unique_ptr<Divider> mDivider;
};

TEST_F(SomeFixture, SomeTest) {
    static uint32_t counter = 0;
    std::cout << "Execution: " << counter << "\n";
    EXPECT_EQ(mDivider->calc(mSome_value, mSome_value), 1);
}
