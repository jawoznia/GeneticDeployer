#include "../include/Chromosome.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

Chromosome::Chromosome(const data::DataHolder& data)
    : mt(rd())
{
    mDevs = data.getDevelopers();
    mManagers = data.getManagers();

    initSolution(data);
    calculateFitness();
}

void Chromosome::initSolution(const data::DataHolder& data)
{
    const auto& seats(data.getSeats());
    const std::uint32_t sizeOfRows = seats.size();
    mSolution.resize(sizeOfRows);
    for (std::uint32_t row = 0; row < sizeOfRows; ++row)
    {
        const std::uint32_t sizeOfColumns = seats[row].size();
        mSolution[row].resize(sizeOfColumns);
        for (std::uint32_t column = 0; column < sizeOfColumns; ++column)
        {
            mSolution[row][column].mType = seats[row][column];
            setPerson(mSolution[row][column]);
        }
    }
    std::cout << "Solution initialized!" << std::endl;
}

void Chromosome::setPerson(Gene& gene)
{
    switch (gene.mType)
    {
        case SeatType::Developer:
            setPerson(gene, mDevs);
            break;
        case SeatType::Manager:
            setPerson(gene, mManagers);
            break;
        case SeatType::Unavailable:
            gene.mPerson = nullptr;
            break;
    }
}

void Chromosome::setPerson(Gene& gene, std::vector<std::shared_ptr<Person>>& people)
{
    if (people.size() == 0)
    {
        return;
    }
    std::uniform_int_distribution<> dis(0, people.size() - 1);
    auto index = dis(mt);
    auto personIter = people.begin();
    std::advance(personIter, index);
    gene.mPerson = *personIter;
    personIter = people.erase(personIter);
}

void Chromosome::calculateFitness()
{
    mFitness = 0;
    const std::uint32_t sizeOfRows = mSolution.size();
    for (std::uint32_t row = 0; row < sizeOfRows; ++row)
    {
        const std::uint32_t sizeOfColumns = mSolution[row].size();
        for (std::uint32_t column = 0; column < sizeOfColumns; ++column)
        {
            calculatePairsScore(row, column, sizeOfRows, sizeOfColumns);
        }
    }
}

void Chromosome::calculatePairsScore(const std::uint32_t row, const std::uint32_t column,
    const std::uint32_t sizeOfRows, const std::uint32_t sizeOfColumns)
{
    const auto& centerPerson(mSolution[row][column].mPerson);
    if (not centerPerson)
    {
        return;
    }
    if (row != 0)
    {
        const auto& person(mSolution[row - 1][column].mPerson);
        if (person)
        {
            addPersonScoreToFitness(*centerPerson, *person);
        }
    }
    if (column != 0)
    {
        const auto& person(mSolution[row][column - 1].mPerson);
        if (person)
        {
            addPersonScoreToFitness(*centerPerson, *person);
        }
    }
    if (row + 1 != sizeOfRows)
    {
        const auto& person(mSolution[row + 1][column].mPerson);
        if (person)
        {
            addPersonScoreToFitness(*centerPerson, *person);
        }
    }
    if (column + 1 != sizeOfColumns)
    {
        const auto& person(mSolution[row][column + 1].mPerson);
        if (person)
        {
            addPersonScoreToFitness(*centerPerson, *person);
        }
    }
}

void Chromosome::addPersonScoreToFitness(const Person& person1, const Person& person2)
{
    std::unordered_set<std::uint32_t> allSkills;
    std::merge(person1.skill_ids.begin(), person1.skill_ids.end(),
        person2.skill_ids.begin(), person2.skill_ids.end(), std::inserter(allSkills, allSkills.begin()));
    std::unordered_set<std::uint32_t> commonSkills;
    std::set_intersection(person1.skill_ids.begin(), person1.skill_ids.end(),
        person2.skill_ids.begin(), person2.skill_ids.end(), std::inserter(commonSkills, commonSkills.begin()));
    const std::uint32_t workPotential = commonSkills.size() * (allSkills.size() - commonSkills.size());
    const std::uint32_t bonusPotential =
        person1.company_id == person2.company_id ? person1.bonus_potential * person2.bonus_potential : 0;

    mFitness += workPotential + bonusPotential;
}

std::uint32_t Chromosome::getFitness()
{
    return mFitness;
}
