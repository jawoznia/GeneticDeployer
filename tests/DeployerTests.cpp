//
// Created by Jan Woźniak on 20-Mar-20.
//

#include "gtest/gtest.h"

#include <memory>
#include "GeneticDeployer.hpp"

class DeployerFixture : public ::testing::Test {
public:
    SomeFixture() : mSome_value(5), mSut(std::make_unique<GeneticDeployer>()) {}

protected:
    std::unique_ptr<GeneticDeployer> mSut;
    uint32_t mSome_value;
    std::unique_ptr<Divider> mDivider;
};

TEST_F(DeployerFixture, SomeTest) {
    sut->start();
}
