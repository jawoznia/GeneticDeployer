//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
#define MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP

#include <memory>

#include "FileReader.hpp"
#include "DataHolder.hpp"

class GeneticDeployer {
public:
    GeneticDeployer();

private:
    void Start();

private:
    std::unique_ptr<data::FileReader> mFileReader;
    std::unique_ptr<data::DataHolder> mDataHolder;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
