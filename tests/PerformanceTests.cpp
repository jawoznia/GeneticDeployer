//
// Created by Jan Woźniak on 05-Jan-21.
//

#include "gtest/gtest.h"

#include <memory>
#include "../include/GeneticDeployer.hpp"
#include "PerformanceParameters.hpp"


class PerformanceFixture : public ::testing::TestWithParam<std::tuple<>> {
public:
    PerformanceFixture() {}

protected:
    std::unique_ptr<GeneticDeployer> mSut;
};

TEST_F(PerformanceFixture, RunForSolar) {
    mSut = std::make_unique<GeneticDeployer>("../data/a_solar.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setNumberOfStopOccurances(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(PerformanceFixture, RunForDream) {
    mSut = std::make_unique<GeneticDeployer>("../data/b_dream.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setNumberOfStopOccurances(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(PerformanceFixture, RunForSoup) {
    mSut = std::make_unique<GeneticDeployer>("../data/c_soup.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setNumberOfStopOccurances(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(PerformanceFixture, RunForMaelstrom) {
    mSut = std::make_unique<GeneticDeployer>("../data/d_maelstrom.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setNumberOfStopOccurances(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(PerformanceFixture, RunForIgloos) {
    mSut = std::make_unique<GeneticDeployer>("../data/e_igloos.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setNumberOfStopOccurances(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(PerformanceFixture, RunForGlitch) {
    mSut = std::make_unique<GeneticDeployer>("../data/f_glitch.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setNumberOfStopOccurances(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

