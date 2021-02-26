//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/FileExporter.hpp"

#include <boost/algorithm/string.hpp>
#include <iostream>

namespace data
{

FileExporter::FileExporter(const std::string& fileName) {
    mStream.open(fileName, std::ofstream::out | std::ofstream::app);
}

FileExporter::~FileExporter() {
    if (mStream.is_open())
        mStream.close();
}

void FileExporter::appendData(const std::string& data) {
    mStream << data << "\n";
}

void FileExporter::appendData(const std::vector<std::string>& data) {
    for (const auto& line : data) {
        mStream << line << "\n";
    }
}

}
