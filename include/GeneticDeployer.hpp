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
    GeneticDeployer(const std::string&);

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
    void checkIfAnySolutionHasDuplicates();
    void sort();

private:
    std::unique_ptr<data::FileReader> mFileReader;
    std::unique_ptr<data::DataHolder> mDataHolder;
    std::vector<std::unique_ptr<Chromosome>> mSolutions;
    std::pair<std::uint32_t, std::uint8_t> mFitnessToOccurance;

    constexpr static std::uint32_t mSizeOfPopulation = 50;
    constexpr static std::uint32_t mNumberOfSelections = 40;
    std::random_device mRd;
    std::mt19937 mMt;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
