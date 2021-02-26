//
// Created by Jan Woźniak on 26-Feb-21.
//

#ifndef GENETIC_DEPLOYER_FILEEXPORTER_HPP_
#define GENETIC_DEPLOYER_FILEEXPORTER_HPP_

#include <fstream>
#include <vector>

namespace data
{

class FileExporter {
public:
    FileExporter(const std::string& fileName);
    ~FileExporter();

    void appendData(const std::string&);
    void appendData(const std::vector<std::string>&);

private:
    std::ofstream mStream;
};

}

#endif // GENETIC_DEPLOYER_FILEEXPORTER_HPP_
