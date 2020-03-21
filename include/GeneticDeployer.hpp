//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
#define MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP

#include <memory>

#include "FileReader.hpp"
#include "DataHolder.hpp"

/*
 *
 * In DataLoader getline create DataHolder and setWidth and setHeight
 *
 * then loadMap
 *
 * Then InitPeople(uint_32 size)
 *
 * AddPerson(std::make_unique<Person>(company, sth, sth..)
 *
 * InitCompanies
 * AddCompany(companyName, sth)
 *
 */

class GeneticDeployer {
public:
    GeneticDeployer();

private:
    void Start();

private:
    std::unique_ptr<data::FileReader> mFileReader;
    std::unique_ptr<data::DataHolder> mDataHandler;
};


#endif //MAYBE_THIS_TIME_TESTS_GENETICDEPLOYER_HPP
