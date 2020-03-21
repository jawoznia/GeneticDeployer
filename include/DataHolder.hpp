//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef GENETIC_DEPLOYER_DATAHOLDER_HPP
#define GENETIC_DEPLOYER_DATAHOLDER_HPP

#include <string>

namespace data
{

class DataHolder {
public:
    explicit DataHolder(const std::string& data);

private:
    void ProcessData();
    const std::string& mData;
};

}

#endif //GENETIC_DEPLOYER_DATAHOLDER_HPP
