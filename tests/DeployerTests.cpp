//
// Created by Jan Woźniak on 20-Mar-20.
//

#include "gtest/gtest.h"

#include <memory>
#include "../include/GeneticDeployer.hpp"

class DeployerFixture : public ::testing::Test {
public:
    DeployerFixture() {}

protected:
    std::unique_ptr<GeneticDeployer> mSut;
};

TEST_F(DeployerFixture, RunForSolar) {
    mSut = std::make_unique<GeneticDeployer>("../data/a_solar.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setOccurancesToStopProgram(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(DeployerFixture, RunForDream) {
    mSut = std::make_unique<GeneticDeployer>("../data/b_dream.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setOccurancesToStopProgram(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(DeployerFixture, RunForSoup) {
    mSut = std::make_unique<GeneticDeployer>("../data/c_soup.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setOccurancesToStopProgram(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(DeployerFixture, RunForMaelstrom) {
    mSut = std::make_unique<GeneticDeployer>("../data/d_maelstrom.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setOccurancesToStopProgram(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(DeployerFixture, RunForIgloos) {
    mSut = std::make_unique<GeneticDeployer>("../data/e_igloos.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setOccurancesToStopProgram(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

TEST_F(DeployerFixture, RunForGlitch) {
    mSut = std::make_unique<GeneticDeployer>("../data/f_glitch.txt");
    mSut->setSizeOfPopulation(50);
    mSut->setOccurancesToStopProgram(5);
    mSut->setNumberOfDescendants(40);
    mSut->start();
}

