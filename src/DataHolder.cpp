//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/DataHolder.hpp"
#include <iostream>

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
    if (words.empty())
    {
        std::cout << "Loaded words are empty. Stopping creating Configuration.\n";
        return;
    }
    SetSeatsWidth(std::stoi(words.at(1)));
    SetSeatsHeight(std::stoi(words.at(0)));

    for (int row_index = 0; row_index < mSeats.size(); ++row_index) {
        for (int column_index = 0; column_index < mSeats[row_index].size(); ++column_index) {
            std::cout << "row_index = " << row_index << "; column_index = " << column_index << "\n";
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

    mWords_iterator = words.begin() + initial_index + 1;
    for (uint32_t i = 0; i < size_of_devs; ++i)
    {
        mDevelopers.at(i) = CreateDeveloper();
    }
}

std::shared_ptr<Person> DataHolder::CreateDeveloper() {
    auto s = *mWords_iterator;
    auto dev(std::make_shared<Person>());

    dev->company_id = insertCompany(*mWords_iterator);

    std::advance(mWords_iterator, 1);
    dev->bonus_potential = std::stoi(std::string(*mWords_iterator));

    std::advance(mWords_iterator, 1);
    const auto skills_size = std::stoi(std::string(*mWords_iterator));

    std::vector<uint32_t> skills(skills_size);
    for (uint32_t i = 0; i < skills_size; ++i) {
        std::advance(mWords_iterator, 1);
        skills.at(i) = insertSkill(*mWords_iterator);
    }
    dev->skill_ids = skills;

    std::advance(mWords_iterator, 1);
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

void DataHolder::SetManagers(const std::vector<std::string> &words) {
    const uint32_t size_of_managers = std::stoi(*mWords_iterator);
    if (size_of_managers == 0)
    {
        return;
    }
    std::cout << "managers size is " << size_of_managers << std::endl;
    mManagers.resize(size_of_managers);

    std::advance(mWords_iterator, 1);
    std::cout << "wolololo" << std::endl;
    for (uint32_t i = 0; i < size_of_managers; ++i) {
        mManagers.at(i) = CreateManager();
    }
}

std::shared_ptr<Person> DataHolder::CreateManager() {
    auto manager(std::make_shared<Person>());
    manager->company_id = insertCompany(*mWords_iterator);

    std::advance(mWords_iterator, 1);
    manager->bonus_potential = std::stoi(*mWords_iterator);
    std::advance(mWords_iterator, 1);
    return std::move(manager);
}

std::vector<std::shared_ptr<Person>> DataHolder::getDevelopers() const
{
    return mDevelopers;
}

std::vector<std::shared_ptr<Person>> DataHolder::getManagers() const
{
    return mManagers;
}

std::vector<std::vector<SeatType>> DataHolder::getSeats() const
{
    return mSeats;
}

}
