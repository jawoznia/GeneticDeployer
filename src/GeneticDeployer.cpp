//
// Created by Jan Woźniak on 21-Mar-20.
//

#include <iostream>

#include "../include/GeneticDeployer.hpp"

GeneticDeployer::GeneticDeployer() : mFileReader(std::make_unique<data::FileReader>("../data/a_solar.txt")) {
}

void GeneticDeployer::Start() {
    std::cout << "Starting data loading.\n";

    mDataHolder = mFileReader->LoadData();
    
    std::cout << "Data loaded. Starting calculation...\n";

    Calculate();
}

/* 
 * 1. Population    - all solutions
 * 2. Chromosome    - one solution
 * 3. Gene          - one seat
 * */

/*
 * 1. Fitness function: It would be nice if chromosome was a class with implemented fitness function.
 * 2. Selection: based on Fitness function. Fittest should survive. But there should be some probability function that would sometimes let less fitests individuals survive. This should create pairs of chromosomes.
 * 3. Crossover: This should randomly merge two chromosomes from pairs into new pair or maybe one individual.
 * 4. Mutation: Random probability for random change of genes.
 * 5. Termination: a) stop if no significant change is made between generations.
 * b) Maybe time.
 * */

void GeneticDeployer::Calculate()
{
    InitPopulation();
    //while (shouldEnd())
}

void GeneticDeployer::InitPopulation()
{

}
