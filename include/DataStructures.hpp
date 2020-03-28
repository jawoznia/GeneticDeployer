//
// Created by Jan Woźniak on 21-Mar-20.
//

#ifndef GENETIC_DEPLOYER_DATASTRUCTURES_HPP
#define GENETIC_DEPLOYER_DATASTRUCTURES_HPP

#include <cstdint>
#include <vector>

enum class SeatType {
    Developer = 0,
    Manager = 1,
    Unavailable = 2
};

struct Developer {
    uint32_t company_id;
    uint32_t bonus_potential;
    std::vector<uint32_t> skill_ids;
};

struct Manager {
    uint32_t company_id;
    uint32_t bonus_potential;
};

#endif //GENETIC_DEPLOYER_DATASTRUCTURES_HPP
