//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
#define MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP

#include "../include/Chromosome.hpp"
#include "../include/DataHolder.hpp"
#include "../include/FileReader.hpp"

#include <memory>
#include <vector>

class GeneticDeployer {
public:
    GeneticDeployer();

    void start();

private:
    bool shouldEnd();

    void initPopulation();
    void calculate();
    std::vector<std::uint32_t> tournamentSelection();
    std::uint32_t getMostFitnessSolutionId(const std::vector<std::uint32_t>&);
    void crossover();
    void mutation();
    void calculateFitness();
    void getMostSuited();
    void printBestAndWorstSolution();

private:
    std::unique_ptr<data::FileReader> mFileReader;
    std::unique_ptr<data::DataHolder> mDataHolder;
    std::vector<std::unique_ptr<Chromosome>> mSolutions;

    std::uint32_t mSizeOfPopulation = 20;
    std::uint32_t mNumberOfSelections = 10;
    std::random_device mRd;
    std::mt19937 mMt;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
