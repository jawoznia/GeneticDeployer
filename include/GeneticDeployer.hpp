//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
#define MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP

#include "../include/Chromosome.hpp"
#include "../include/DataHolder.hpp"
#include "../include/FileExporter.hpp"
#include "../include/FileReader.hpp"

#include <memory>
#include <vector>
#include <chrono>

class GeneticDeployer {
public:
    GeneticDeployer(const std::string&);

    void setSizeOfPopulation(std::uint32_t);
    void setNumberOfStopOccurances(std::uint32_t);
    void setNumberOfDescendants(std::uint32_t);

    void start();

private:
    bool shouldEnd();
    bool isDurationTooLong();
    bool isFitnessPeakFound();

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
    void saveScoreToFile(std::uint32_t fitness);

private:
    std::unique_ptr<data::FileReader> mFileReader;
    std::unique_ptr<data::FileExporter> mFileExporter;
    std::unique_ptr<data::DataHolder> mDataHolder;
    std::vector<std::unique_ptr<Chromosome>> mSolutions;
    std::pair<std::uint32_t, std::uint32_t> mFitnessToOccurance;

    const std::string mFileName;
    std::uint32_t mSizeOfPopulation;
    std::uint32_t mNumberOfSelections;
    std::uint32_t mOccurancesToStopProgram;
    std::random_device mRd;
    std::mt19937 mMt;
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
