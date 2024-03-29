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

static std::uint32_t id{0};

struct Person {
    Person() : person_id(id++)
    {
    }

    bool operator ==(const Person& p) {
        return person_id == p.person_id;
    }

    const std::uint32_t person_id;
    std::uint32_t company_id;
    std::uint32_t bonus_potential;
    std::vector<std::uint32_t> skill_ids;
};

#endif //GENETIC_DEPLOYER_DATASTRUCTURES_HPP
