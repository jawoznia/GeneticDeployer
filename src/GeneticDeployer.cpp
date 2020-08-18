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
 * 1. Fitness function: It would be nice if chromosome was a class with implemented fitness function.
 * 2. Selection: based on Fitness function. Fittest should survive. But there should be some probability function that would sometimes let less fitests individuals survive. This should create pairs of chromosomes.
 * 3. Crossover: This should randomly merge two chromosomes from pairs into new pair or maybe one individual.
 * 4. Mutation: Random probability for random change of genes.
 * 5. Termination: a) stop if no significant change is made between generations.
 * b) Maybe time.
 * */

/*
 * Chromosome -> handle solution and it's score. Also it should have logic to calculate fitness.
 *              -> store also shared pointer to all developers and managers
 *              3
 * GeneticDeployer -> create random solutions stored in std::array
 *                  -> think about some way to swap data between them.
 */

void GeneticDeployer::calculate()
{
    initPopulation();
    const auto idsForCrossover = tournamentSelection();
    crossover(idsForCrossover);
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

void GeneticDeployer::crossover(const std::vector<std::uint32_t>& ids)
{
    for (std::uint32_t i = 0; i < mNumberOfSelections; i += 2)
    {
        createDescendatsFor(*mSolutions[i], *mSolutions[i + 1]);
    }
}

void GeneticDeployer::createDescendatsFor(const Chromosome& parent1, const Chromosome& parent2)
{
    std::uniform_int_distribution<> disStart(0, parent1.mSolution.size() - 1);
    const std::uint32_t startIndex(disStart(mMt));
    std::uniform_int_distribution<> disFinish(startIndex, parent1.mSolution.size() - 1);
    const std::uint32_t finishIndex(disFinish(mMt));
    std::unique_ptr<Chromosome> descendant(Chromosome::getDescendant(parent1, parent2));
}
