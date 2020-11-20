#include "../include/Chromosome.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

Chromosome::Chromosome() = default;

Chromosome::~Chromosome() = default;

Chromosome::Chromosome(const data::DataHolder& data)
{
    mDevs = data.getDevelopers();
    mManagers = data.getManagers();

    initSolution(data);
    calculateFitness();
}

std::random_device Chromosome::rd;
std::mt19937 Chromosome::mt = std::mt19937(Chromosome::rd());

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

std::unique_ptr<Chromosome> Chromosome::getDescendant(const Chromosome& parent1, const Chromosome& parent2)
{
    auto descendant(std::make_unique<Chromosome>(parent1, parent2));
    doCrossover(parent1, parent2);
    return std::move(descendant);
}

Chromosome::Chromosome(const Chromosome& parent1, const Chromosome& parent2)
{
    const auto& solution(parent1.mSolution);
    const std::uint32_t sizeOfRows = solution.size();
    mSolution.resize(sizeOfRows);
    for (std::uint32_t row = 0; row < sizeOfRows; ++row)
    {
        const std::uint32_t sizeOfColumns = solution[row].size();
        mSolution[row].resize(sizeOfColumns);
        for (std::uint32_t column = 0; column < sizeOfColumns; ++column)
        {
            mSolution[row][column].mType = solution[row][column].mType;
            mSolution[row][column].mPerson = nullptr;
            if (mSolution[row][column].mType == SeatType::Developer)
            {
                mDevs.push_back(solution[row][column].mPerson);
            }
            else if (mSolution[row][column].mType == SeatType::Manager)
            {
                mManagers.push_back(solution[row][column].mPerson);
            }
        }
    }
    mDevs.reserve(mDevs.size() + parent1.mDevs.size());
    mDevs.insert(mDevs.end(), parent1.mDevs.begin(), parent1.mDevs.end());
    mManagers.reserve(mManagers.size() + parent1.mManagers.size());
    mManagers.insert(mManagers.end(), parent1.mManagers.begin(), parent1.mManagers.end());
}

void Chromosome::doCrossover(const Chromosome& parent1, const Chromosome& parent2)
{
    std::uint32_t sizeOfRows = parent1.mSolution.size();
    std::uniform_int_distribution<> lowerDis(0, sizeOfRows);
    auto lowerIndex = lowerDis(mt);
    std::uniform_int_distribution<> upperDis(lowerIndex, sizeOfRows);
    auto upperIndex = upperDis(mt);

    // Ok I have start and finnish indexes.
    // Now I need to:
    // 1. copy from one parent range between those indexes
    // 2. find from second parent those managers/developers that were not used in here
    // 3. create descendant with range from first one in place and people from second one filled in free seats.

    // Writing it realy stupid to just move on
    //
    auto firstParentGenes()
}
