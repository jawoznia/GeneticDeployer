//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_FILEREADER_HPP
#define MAYBE_THIS_TIME_TESTS_FILEREADER_HPP

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "../include/DataHolder.hpp"

namespace data
{

class FileReader {
public:
    FileReader(const std::string& fileName);
    ~FileReader();

    std::unique_ptr<DataHolder> LoadData();

private:
    void ProcessStream();

private:
    std::string mData;
    std::ifstream mStream;
    std::unique_ptr<data::DataHolder> mDataHolder;
};

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
}

#endif //MAYBE_THIS_TIME_TESTS_FILEREADER_HPP
