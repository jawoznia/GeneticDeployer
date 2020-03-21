//
// Created by Jan Woźniak on 21-Mar-20.
//

#include <iostream>

#include "../include/GeneticDeployer.hpp"

GeneticDeployer::GeneticDeployer() : mFileReader(std::make_unique<data::FileReader>("../data/a_solar.txt")) {
    Start();
}

void GeneticDeployer::Start() {
    std::cout << "Starting data loading.\n";

    mDataHandler = std::make_unique<data::DataHolder>(mFileReader->LoadData());
}
