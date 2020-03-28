//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "DataHolder.hpp"

namespace data
{

void DataHolder::SetSeatsWidth(const uint32_t size) {
    mSeats.resize(size);
}

void DataHolder::SetSeatsHeight(const uint32_t size) {
    for (auto& row : mSeats) {
        row.resize(size, SeatType::Unavailable);
    }
}

void DataHolder::SetSeats(const std::vector<std::string>& words) {
    SetSeatsWidth(std::stoi(words.at(1)));
    SetSeatsHeight(std::stoi(words.at(0)));

    for (int row_index = 0; row_index < mSeats.size(); ++row_index) {
        for (int column_index = 0; column_index < mSeats[row_index].size(); ++column_index) {
            SetSeat(row_index, column_index, words.at(row_index + 2).at(column_index));
        }
    }
}

void DataHolder::SetSeat(uint32_t width, uint32_t height, const char val) {
    switch (val)
    {
        case '_':
            mSeats[width][height] = SeatType::Developer;
            break;
        case 'M':
            mSeats[width][height] = SeatType::Manager;
            break;
        default:
            mSeats[width][height] = SeatType::Unavailable;
    }
}

void DataHolder::SetDevelopers(const std::vector<std::string> &words) {
    const uint32_t initial_index = std::stoi(words.at(1)) + 2;
    const uint32_t size_of_devs = std::stoi(words.at(initial_index));

    mDevelopers.resize(size_of_devs);

    auto words_iterator = words.begin() + initial_index + 1;
    for (uint32_t i = 0; i < size_of_devs; ++i)
    {
        mDevelopers.at(i) = CreateDeveloper(words_iterator);
    }
}

Developer DataHolder::CreateDeveloper(words_it &it) {
    auto s = *it;
    Developer dev;

    dev.company_id = insertCompany(*it);

    std::advance(it, 1);
    dev.bonus_potential = std::stoi(std::string(*it));

    std::advance(it, 1);
    const auto skills_size = std::stoi(std::string(*it));

    std::vector<uint32_t> skills(skills_size);
    for (uint32_t i = 0; i < skills_size; ++i) {
        std::advance(it, 1);
        skills.at(i) = insertSkill(*it);
    }
    dev.skill_ids = skills;

    std::advance(it, 1);
    return dev;
}

uint32_t DataHolder::insertCompany(const std::string& company_name) {
    static uint32_t company_id = 0;
    auto inserted_company = mCompanies.insert({company_name, company_id});
    return inserted_company.second ? company_id++ : inserted_company.first->second;
}

uint32_t DataHolder::insertSkill(const std::string& skill_name) {
    static uint32_t skill_id = 0;
    auto inserted_skill = mSkills.insert({skill_name, skill_id});
    return inserted_skill.second ? skill_id++ : inserted_skill.first->second;
}

}
