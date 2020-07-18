#include "../include/Chromosome.hpp"
#include <iostream>

Chromosome::Chromosome(const data::DataHolder& data)
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
            mSolution[row][column].mPerson = std::make_shared<Person>();
        }
    }
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
    if (row != 0)
        addPersonScoreToFitness(mSolution[row][column], mSolution[row - 1][column]);
    else if (column != 0)
        addPersonScoreToFitness(mSolution[row][column], mSolution[row][column - 1]);
    else if (row + 1 != sizeOfRows)
        addPersonScoreToFitness(mSolution[row][column], mSolution[row + 1][column]);
    else if (column + 1 != sizeOfColumns)
        addPersonScoreToFitness(mSolution[row][column], mSolution[row][column + 1]);
}

void Chromosome::addPersonScoreToFitness(const Gene& , const Gene&)
{

}

std::uint32_t Chromosome::getFitness()
{
    return mFitness;
}

