//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
#define MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP

#include <memory>

#include "../include/FileReader.hpp"
#include "../include/DataHolder.hpp"

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
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
