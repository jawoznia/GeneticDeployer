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
using words_it = std::vector<std::string>::const_iterator;

class DataHolder {
public:
    DataHolder() = default;
    void SetSeats(const std::vector<std::string>&);
    void SetDevelopers(const std::vector<std::string>&);
    void SetManagers(const std::vector<std::string>&);

private:
    void SetSeat(uint32_t, uint32_t, const char);
    void SetSeatsWidth(const uint32_t);
    void SetSeatsHeight(const uint32_t);

    Developer CreateDeveloper(words_it &);

    uint32_t insertCompany(const std::string&);
    uint32_t insertSkill(const std::string&);

private:
    // Will be holding unique companies with their ids
    std::map<const std::string, const uint32_t> mCompanies;

    // Will be holding unique skills with their ids
    std::map<const std::string, const uint32_t> mSkills;

    // Will hold height x width map of desks
    std::vector<std::vector<SeatType>> mSeats;

    // Will hold developers
    std::vector<Developer> mDevelopers;

};

}

#endif //GENETIC_DEPLOYER_DATAHOLDER_HPP
