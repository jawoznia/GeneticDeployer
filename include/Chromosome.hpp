#ifndef GENETIC_DEPLOYER_CHROMOSOME_HPP
#define GENETIC_DEPLOYER_CHROMOSOME_HPP

#include "DataHolder.hpp"
#include "DataStructures.hpp"

#include <memory>
#include <vector>

class Gene
{
public:
   SeatType mType; 
   std::shared_ptr<Person> mPerson;
};

class Chromosome
{
public:
    explicit Chromosome(const data::DataHolder&);
    void initSolution(const data::DataHolder&);
    void calculateFitness();
    void calculatePairsScore(const std::uint32_t row, const std::uint32_t column,
        const std::uint32_t sizeOfRows, const std::uint32_t sizeOfColumns);
    void addPersonScoreToFitness(const Gene&, const Gene&);
    std::uint32_t getFitness();

public:
    std::uint32_t mFitness;
    std::vector<std::vector<Gene>> mSolution;
    std::vector<std::shared_ptr<Person>> mDevs;
    std::vector<std::shared_ptr<Person>> mManagers;
};

#endif //GENETIC_DEPLOYER_CHROMOSOME_HPP
