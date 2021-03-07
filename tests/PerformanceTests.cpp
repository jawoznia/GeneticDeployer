//
// Created by Jan Woźniak on 05-Jan-21.
//

#include "gtest/gtest.h"

#include <memory>
#include "../include/GeneticDeployer.hpp"
#include "PerformanceParameters.hpp"


class PerformanceFixture : public ::testing::TestWithParam<data::PerformanceParameters> {
public:
    PerformanceFixture() {}

protected:
    std::unique_ptr<GeneticDeployer> mSut;
};

INSTANTIATE_TEST_SUITE_P(PerformanceTests, PerformanceFixture,
    ::testing::ValuesIn(data::getPerformanceParameters()));

TEST_P(PerformanceFixture, MakeResearch) {
    auto param = GetParam();
    mSut = std::make_unique<GeneticDeployer>(param.fileName);
    mSut->setSizeOfPopulation(param.sizeOfPopulation);
    mSut->setOccurancesToStopProgram(param.occurancesToStopProgram);
    mSut->setNumberOfDescendants(param.numberOfDescendants);
    mSut->start();
}

