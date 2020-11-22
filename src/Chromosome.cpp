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

Chromosome::Chromosome(const Chromosome& parent1, const Chromosome& parent2)
{
/*    const auto& solution(parent1.mSolution);
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
*/
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
            insertPerson(parent2.mSolution[row][column].mPerson);
            /*
             *  if (find(person in mDevs or mManagers))
             *    assign Person to this place and delete it from mDevs/mManagers
             *  else
             *    assign first left person to that place
             * */
        }
    }

    // Now we need to fill remaing seats with basing on solution from second parent.
    // It could be done for example:
    // 1. Fill mDevs and mManagers to get info about which people are free to be seated.
    // 2. Iterate over remaining seats and if parent2 has there unused dev or manager then you are free to sit there this person.
    //    If this person is already taken we can do it in two ways:
    //      a) iterate further filling seats with people that are not taken. Then come back and for every free seat add random person
    //      b) if person is already sitting just put there random person (but this can cause that next seat could be left without a person
    //          as we would just take one that was sitting there in parent2. So I'm not sure if this would be a great idea as descendants would be
    //          almost mutaded in time of crossover.
}

void Chromosome::insertPerson(const std::shared_ptr<Person> person) {
    if (isPersonFree(person)) {
        // insertPerson()parent2.mSolution[row][column])
    } else {
        // insertPerson(mDevs[0]);
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

bool Chromosome::isPersonFree(const std::shared_ptr<Person> person) const {
    return std::find(mDevs.begin(), mDevs.end(), person) != mDevs.end() or
        std::find(mManagers.begin(), mManagers.end(), person) != mManagers.end();
}

