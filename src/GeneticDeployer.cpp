//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/GeneticDeployer.hpp"

#include "../include/helpers/Printers.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

GeneticDeployer::GeneticDeployer(const std::string& filename)
    : mFileReader(std::make_unique<data::FileReader>(filename))
    , mFitnessToOccurance(std::make_pair(0, 0))
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
 * 4. [DONE] Mutation: Random probability for random change of genes.
 * 5. Termination: a) stop if no significant change is made between generations.
 * b) Maybe time.
 * */

void GeneticDeployer::calculate()
{
    static constexpr std::uint32_t numberOfGenerations = 100;
    initPopulation();
    //for (std::uint32_t i = 0; i < numberOfGenerations; ++i) {
    std::uint32_t generation = 0;
    while (not shouldEnd()) {
        std::cout << generation << " generation.\n";
        if (generation++ == numberOfGenerations) {
            std::cout << "Stopping due to generation limit\n";
            break;
        }
        //checkIfAnySolutionHasDuplicates();
        crossover();
        std::cout << "Current best fitness " << (*mSolutions.begin())->mFitness << "\n";
        //checkIfAnySolutionHasDuplicates();
        mutation();
        //checkIfAnySolutionHasDuplicates();
        calculateFitness();
        sort();
    }
    /*int i = 0;
    for (const auto& solution : mSolutions) {
        std::cout << i++ << ". Solution's fitness is " << solution->mFitness << "\n";
    }*/
    printBestAndWorstSolution();
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

    descendants.emplace_back(std::make_unique<Chromosome>(*mSolutions[*ids.begin()], *mSolutions[*ids.rbegin()]));
    for (std::uint32_t i = 0; i < mNumberOfSelections - 1; ++i)
    {
        descendants.emplace_back(std::make_unique<Chromosome>(*mSolutions[ids[i]], *mSolutions[ids[i + 1]]));
    }
    getMostSuited();
    mSolutions.insert(mSolutions.end(),
        std::make_move_iterator(descendants.begin()),
        std::make_move_iterator(descendants.end()));
}

void GeneticDeployer::mutation() {
    std::uniform_real_distribution<> mutationProbabilityDis(0, 1);
    for (const auto& solution : mSolutions) {
        if (mutationProbabilityDis(mMt) < 0.15) {
            solution->mutate();
        }
    }
}

void GeneticDeployer::calculateFitness() {
    for (const auto& solution : mSolutions) {
        solution->calculateFitness();
    }
}

void GeneticDeployer::getMostSuited() {
    static constexpr std::uint32_t numberOfParentsToNextGeneration = 10;
    sort();
    mSolutions.erase(mSolutions.begin() + numberOfParentsToNextGeneration, mSolutions.end());
}

void GeneticDeployer::sort() {
    std::sort(mSolutions.begin(), mSolutions.end(),
        [](const std::unique_ptr<Chromosome>& chr1, const std::unique_ptr<Chromosome>& chr2) {
            return chr1->mFitness > chr2->mFitness;
        });
}

void GeneticDeployer::printBestAndWorstSolution() {
    sort();
    std::cout << "printing best " << (*mSolutions.begin())->mFitness << "\n";
//    printers::printSolution(**mSolutions.begin());
//    std::cout << "Printing worst\n";
//    printers::printSolution(**mSolutions.rbegin());
}

void GeneticDeployer::checkIfAnySolutionHasDuplicates() {
    for (const auto& solution : mSolutions) {
        if (solution->hasDuplicates()) {
            std::cout << "Gotcha!\n";
            throw std::runtime_error("Duplicate found. Stopping program!");
        }
    }
}

bool GeneticDeployer::shouldEnd() {
    static constexpr std::uint8_t occurancesToStopProgram = 5;
    const auto& currentBestFitness = (*mSolutions.begin())->mFitness;
    if (mFitnessToOccurance.first == currentBestFitness) {
        if ((++mFitnessToOccurance.second) == occurancesToStopProgram) {
            return true;
        }
    } else {
        mFitnessToOccurance = std::make_pair(currentBestFitness, 1);
    }
    return false;
}

