//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
#define MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP

#include <memory>

#include "FileReader.hpp"


class GeneticDeployer {
public:
    GeneticDeployer();

private:
    void Start();

private:
    std::unique_ptr<data::FileReader> mFileReader;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
