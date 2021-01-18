#include "../include/Chromosome.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <set>

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
    //std::cout << "Solution initialized!" << std::endl;
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
    auto indexShift = dis(mt);
    auto personIter = people.begin();
    std::advance(personIter, indexShift);
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
        person2.skill_ids.begin(), person2.skill_ids.end(),
        std::inserter(allSkills, allSkills.begin()));
    std::unordered_set<std::uint32_t> commonSkills;
    std::set_intersection(person1.skill_ids.begin(), person1.skill_ids.end(),
        person2.skill_ids.begin(), person2.skill_ids.end(),
        std::inserter(commonSkills, commonSkills.begin()));
    const std::uint32_t workPotential = commonSkills.size() * (allSkills.size() - commonSkills.size());
    const std::uint32_t bonusPotential =
        person1.company_id == person2.company_id ? person1.bonus_potential * person2.bonus_potential : 0;

    mFitness += workPotential + bonusPotential;
}

std::uint32_t Chromosome::getFitness()
{
    return mFitness;
}

Chromosome::Chromosome(const Chromosome& parent1, const Chromosome& parent2)
{
    mSolution = parent1.mSolution;
    mDevs = parent1.mDevs;
    mManagers = parent1.mManagers;
    doCrossover(parent2);
}

// Will make crossover using one random gene as an pivot.
void Chromosome::doCrossover(const Chromosome& parent2)
{
    std::uint32_t rowIndex = getRandomRow();
    std::uint32_t columnIndex = getRandomColumn();

    for (std::uint32_t row = rowIndex; row < mSolution.size(); ++row) {
        for (std::uint32_t column = columnIndex; column < mSolution[0].size(); ++column) {
            if (parent2.mSolution[row][column].mType == SeatType::Unavailable) {
                continue;
            }
            insertPerson(parent2.mSolution[row][column], row, column);
        }
    }
}

void Chromosome::insertPerson(const Gene& gene, std::uint32_t row, std::uint32_t column) {
    if (gene.mType == SeatType::Manager) {
        addToContainer(mManagers, gene.mPerson, row, column);
    }
    else if (gene.mType == SeatType::Developer) {
        addToContainer(mDevs, gene.mPerson, row, column);
    }
}

void Chromosome::addToContainer(std::vector<std::shared_ptr<Person>>& people,
        const std::shared_ptr<Person>& person, std::uint32_t row, std::uint32_t column) {
    const auto& foundPerson = std::find(people.begin(), people.end(), person);
    if (foundPerson != people.end()) {
        std::swap(mSolution[row][column].mPerson, *foundPerson);
    } else if (not people.empty()) {
        std::swap(mSolution[row][column].mPerson, people[0]);
    }
}

// Simple swap mutation.
// For @numberOfMutation times pair of people with same position are chosen and swapped
void Chromosome::mutate() {
    static constexpr int numberOfMutation = 2;
    for (int i = 0; i < numberOfMutation; ++i) {
        std::uint32_t firRow;
        std::uint32_t firColumn;
        do {
            firRow = getRandomRow();
            firColumn = getRandomColumn();
        } while (mSolution[firRow][firColumn].mType == SeatType::Unavailable);
        std::uint32_t secRow;
        std::uint32_t secColumn;
        do {
            secRow = getRandomRow();
            secColumn = getRandomColumn();
        } while (mSolution[firRow][firColumn].mType != mSolution[secRow][secColumn].mType);
        std::swap(mSolution[firRow][firColumn], mSolution[firRow][firColumn]);
   }
}

std::uint32_t Chromosome::getRandomColumn() const {
    std::uint32_t sizeOfColumns = mSolution[0].size();
    std::uniform_int_distribution<> columnDis(0, sizeOfColumns - 1);
    return columnDis(mt);
}

std::uint32_t Chromosome::getRandomRow() const {
    std::uint32_t sizeOfRows = mSolution.size();
    std::uniform_int_distribution<> rowDis(0, sizeOfRows - 1);
    return rowDis(mt);
}

bool Chromosome::hasDuplicates() {
    std::set<std::uint32_t> uniqueIds;
    for (const auto& row : mSolution) {
        for (const auto& gene : row) {
            if (gene.mType == SeatType::Unavailable) {
                continue;
            }
            auto result = uniqueIds.insert(gene.mPerson->person_id);
            bool wasValuePresent = not result.second;
            if (wasValuePresent) {
                return true;
            }
        }
    }
    return false;
}

