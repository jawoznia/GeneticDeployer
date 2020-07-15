#ifndef GENETIC_DEPLOYER_CHROMOSOME_HPP
#define GENETIC_DEPLOYER_CHROMOSOME_HPP

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
    void calculateFitness();
    std::uint32_t getFitness();

public:
    std::uint32_t mFitness;
    std::vector<std::vector<Gene>> mSolution;
};

#endif //GENETIC_DEPLOYER_CHROMOSOME_HPP

