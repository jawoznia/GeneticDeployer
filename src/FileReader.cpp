//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/FileReader.hpp"

namespace data
{

FileReader::FileReader(const std::string &&fileName) : mStream(fileName) {
    mStream.open(fileName, std::ios::in);
}

FileReader::~FileReader() {
    if (mStream.is_open())
        mStream.close();
}

std::string FileReader::LoadData() {
    if (mStream.is_open())
        return std::string(std::istreambuf_iterator<char>(mStream), {});
    return std::string{"Couldn't load data. File is not open."};
}

}
