//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/FileReader.hpp"

#include <boost/algorithm/string.hpp>
#include <iostream>

namespace data
{

FileReader::FileReader(const std::string &&fileName) : mStream(fileName), mDataHolder(std::make_unique<DataHolder>()) {
    mStream.open(fileName, std::ios::in);
    ProcessStream();
}

FileReader::~FileReader() {
    if (mStream.is_open())
        mStream.close();
}

std::unique_ptr<DataHolder> FileReader::LoadData() {
    std::vector<std::string> words;
    boost::split(words, mData, [](char c){return c == ' ' or c == '\n';} );

    mDataHolder->SetSeats(words);
    mDataHolder->SetDevelopers(words);
    mDataHolder->SetManagers(words);
    std::cout << "Data loaded" << std::endl;

    return std::move(mDataHolder);
}

void FileReader::ProcessStream() {
    if (mStream.is_open()){
        mData = std::string(std::istreambuf_iterator<char>(mStream), {});
        mStream.close();
    }
}

}
