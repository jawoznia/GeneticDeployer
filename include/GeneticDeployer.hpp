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

    void Start();

private:
    bool ShouldEnd();

    void InitPopulation();
    void Calculate();

private:
    std::unique_ptr<data::FileReader> mFileReader;
    std::unique_ptr<data::DataHolder> mDataHolder;
    std::vector<Chromosome> mSolution;

    std::uint32_t mSizeOfPopulation;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
