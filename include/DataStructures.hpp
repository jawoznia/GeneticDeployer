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

struct Person {
    uint32_t bonus_potential;
    uint32_t company_id;
    std::vector<uint32_t> skill_ids;
};

#endif //GENETIC_DEPLOYER_DATASTRUCTURES_HPP
