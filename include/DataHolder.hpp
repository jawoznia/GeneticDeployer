//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef GENETIC_DEPLOYER_DATAHOLDER_HPP
#define GENETIC_DEPLOYER_DATAHOLDER_HPP

#include <map>
#include <string>

#include "DataStructures.hpp"

namespace data
{

class DataHolder {
public:
    explicit DataHolder();
    void SetSeats(const std::vector<std::string>&);
private:
    void SetSeat(uint32_t, uint32_t, const char);
    void SetSeatsWidth(const uint32_t);
    void SetSeatsHeight(const uint32_t);

private:
    // Will be holding unique companies with their ids
    std::map<std::string, uint32_t> mCompanies;
    // Will be holding unique developers with their ids
    std::map<std::string, uint32_t> mDevelopers;
    // Will be holding unique managers with their ids
    std::map<std::string, uint32_t> mManagers;

    // Will hold height x width map of desks
    std::vector<std::vector<SeatType>> mSeats;
};

}

#endif //GENETIC_DEPLOYER_DATAHOLDER_HPP
