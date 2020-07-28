//
// Created by Jan Woźniak on 20-Mar-20.
//

#include "gtest/gtest.h"

#include <memory>
#include "../include/GeneticDeployer.hpp"

class DeployerFixture : public ::testing::Test {
public:
    DeployerFixture() : mSut(std::make_unique<GeneticDeployer>()) {}

protected:
    std::unique_ptr<GeneticDeployer> mSut;
};

TEST_F(DeployerFixture, ShouldCalculateFitness) {
    std::cout << "Starting Deployer Test.\n";
    mSut->start();
}
