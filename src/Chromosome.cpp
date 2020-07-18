#include "../include/Chromosome.hpp"
#include <iostream>

Chromosome::Chromosome(const data::DataHolder& data)
{
    mFitness = 0;
    mDevs = data.getDevelopers();
    mManagers = data.getManagers();

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

}

std::uint32_t Chromosome::getFitness()
{
    return mFitness;
}

