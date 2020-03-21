//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef MAYBE_THIS_TIME_TESTS_FILEREADER_HPP
#define MAYBE_THIS_TIME_TESTS_FILEREADER_HPP

#include <string>
#include <fstream>

namespace data
{

class FileReader {
public:
    FileReader(const std::string&& fileName);
    ~FileReader();

    std::string LoadData();

private:

    std::ifstream mStream;
};

}

#endif //MAYBE_THIS_TIME_TESTS_FILEREADER_HPP
