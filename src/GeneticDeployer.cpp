//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/GeneticDeployer.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>

GeneticDeployer::GeneticDeployer()
    : mFileReader(std::make_unique<data::FileReader>("../data/a_solar.txt"))
    , mMt(mRd())
{
}

void GeneticDeployer::start() {
    std::cout << "Starting data loading.\n";

    mDataHolder = mFileReader->LoadData();
    
    std::cout << "Data loaded. Starting calculation...\n";

    calculate();
}

/* 
 * 1. Population    - all solutions
 * 2. Chromosome    - one solution
 * 3. Gene          - one seat
 * */

/*
 * 1. [DONE] Fitness function: It would be nice if chromosome was a class with implemented fitness function.
 * 2. [PARTIALY DONE] Selection: based on Fitness function. Fittest should survive. But there should be some probability function that would sometimes let less fitests individuals survive. This should create pairs of chromosomes.
 * 3. [DONE] Crossover: This should randomly merge two chromosomes from pairs into new pair or maybe one individual.
 * 4. Mutation: Random probability for random change of genes.
 * 5. Termination: a) stop if no significant change is made between generations.
 * b) Maybe time.
 * */

void GeneticDeployer::calculate()
{
    initPopulation();
    for (int i = 0; i < 300; ++i) {
        crossover();
        mutate();
    }
}

void GeneticDeployer::initPopulation()
{
    mSolutions.resize(mSizeOfPopulation);
    for (auto& solution : mSolutions)
    {
        solution = std::make_unique<Chromosome>(*mDataHolder);
    }    
}

std::vector<std::uint32_t> GeneticDeployer::tournamentSelection()
{
    std::vector<std::uint32_t> winningIds(mNumberOfSelections);
    std::uniform_int_distribution<> dis(0, mSolutions.size() - 1);
    for (auto& winningId : winningIds)
    {
        const static std::uint32_t sizeOfSingleTournament = 5;
        std::vector<std::uint32_t> ids(sizeOfSingleTournament);
        for (auto& id : ids)
        {
            id = dis(mMt);
        }
        winningId = getMostFitnessSolutionId(ids);
    }
    return winningIds;
}

std::uint32_t GeneticDeployer::getMostFitnessSolutionId(const std::vector<std::uint32_t>& ids)
{
    std::uint32_t maxVal = std::numeric_limits<std::uint32_t>::min();
    std::uint32_t bestId = 0;
    for (const auto id : ids)
    {
        if (maxVal < mSolutions[id]->getFitness())
        {
            bestId = id;
        }
    }
    return bestId;
}

void GeneticDeployer::crossover()
{
    const auto ids = tournamentSelection();
    std::vector<std::unique_ptr<Chromosome>> descendants;

    for (std::uint32_t i = 0; i < mNumberOfSelections - 1; i += 2)
    {
        descendants.emplace_back(std::make_unique<Chromosome>(*mSolutions[ids[i]], *mSolutions[ids[i + 1]]));
    }
    // and what now? descendants are created. Now should they be stored in some other vector. And what about mutation.
    // Should descendants be mutated too? Need to find info about this.
    // Neverheless as crossover seem to be done this project is I think like 85% done for alpha release.
}

void GeneticDeployer::createDescendatsFor(const Chromosome& parent1, const Chromosome& parent2)
{
    auto descendant(std::make_unique<Chromosome>(parent1, parent2));
}

void GeneticDeployer::mutate() {

}

