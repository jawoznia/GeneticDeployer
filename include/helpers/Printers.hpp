#include <iostream>
#include "../Chromosome.hpp"

namespace printers
{

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<Gene>>& solution) {
    os << "\n";
    for (const auto& row : solution) {
        for (const auto& gene : row) {
            if (gene.mType == SeatType::Unavailable) {
                os << "Un ";
            } else {
                os << gene.mPerson->person_id << " ";
            }
        }
        os << "\n";
    }
    return os;
}

void printSolution(const Chromosome& solution) {
    std::cout << "Solution's fitness is " << solution.mFitness << " calculated for " << solution.mSolution << "\n";
}

void printPerson() {
    
}

}
