#include "../include/Chromosome.hpp"

Chromosome::Chromosome(const data::DataHolder& data)
{
    mFitness = 0;
    mDevs = data.getDevelopers();
    mManagers = data.getManagers();

    const std::uint32_t sizeOfRows = data.getSeats().size();
    mSolution.reserve(sizeOfRows);
    for (std::uint32_t row = 0; row < sizeOfRows; ++row)
    {
        const std::uint32_t sizeOfColumns = data.getSeats().at(row).size();
        mSolution.at(row).reserve(sizeOfColumns);
        for (std::uint32_t column = 0; column < sizeOfColumns; ++column)
        {
            mSolution.at(row).at(column).mType = data.getSeats().at(row).at(column);
            mSolution.at(row).at(column).mPerson = std::make_shared<Person>();
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

