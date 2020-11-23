#ifndef GENETIC_DEPLOYER_CHROMOSOME_HPP
#define GENETIC_DEPLOYER_CHROMOSOME_HPP

#include "DataHolder.hpp"
#include "DataStructures.hpp"

#include <memory>
#include <random>
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
    Chromosome(const Chromosome& parent1, const Chromosome& parent2);
    Chromosome(const Chromosome& other) = delete;
    Chromosome(Chromosome&& other) = delete;
    Chromosome& operator=(const Chromosome& other) = delete;
    Chromosome& operator=(Chromosome&& other) = delete;
    ~Chromosome();

    void initSolution(const data::DataHolder&);
    void calculateFitness();
    void calculatePairsScore(const std::uint32_t row, const std::uint32_t column,
        const std::uint32_t sizeOfRows, const std::uint32_t sizeOfColumns);
    void addPersonScoreToFitness(const Person&, const Person&);
    std::uint32_t getFitness();
    void setPerson(Gene& gene);
    void setPerson(Gene& gene, std::vector<std::shared_ptr<Person>>& people);

private:
    Chromosome();
    void doCrossover(const Chromosome&);
    std::uint32_t getRandomColumn() const;
    std::uint32_t getRandomRow() const;
    bool isPersonFree(const std::shared_ptr<Person>) const;
    void insertPerson(const Gene&, std::uint32_t, std::uint32_t);
    void addToContainer(std::vector<std::shared_ptr<Person>>&, std::shared_ptr<Person>, std::uint32_t, std::uint32_t);

public:
    std::uint32_t mFitness;
    std::vector<std::vector<Gene>> mSolution;
    std::vector<std::shared_ptr<Person>> mDevs;
    std::vector<std::shared_ptr<Person>> mManagers;

private:
    static std::random_device rd;
    static std::mt19937 mt;
};

#endif //GENETIC_DEPLOYER_CHROMOSOME_HPP

