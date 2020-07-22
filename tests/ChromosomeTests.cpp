//
// Created by Jan Woźniak on 20-Mar-20.
//

#include "../include/Chromosome.hpp"
#include "../include/DataHolder.hpp"

#include "gtest/gtest.h"

#include <memory>

class ChromosomeFixture : public ::testing::Test {
public:
    ChromosomeFixture() {}

    std::vector<std::string> prepareStringVec()
    {
        return {
            "5",
            "3",
            "#####",
            "#_##_",
            "#MM__",
            "10",
            "opn", "7", "2", "java", "bpm",
            "clstr", "5", "2", "python", "azure",
            "opn", "8", "2", "python", "java",
            "com_vl", "4", "3", "java", "cybersecurity", "big_data",
            "mac", "1", "2", "nlp", "big_data",
            "clstr", "3", "2", "azure", "c#",
            "com_vl", "6", "2", "cybersecurity", "python",
            "opn", "2", "3", "bpm", "python", "project_management",
            "ble", "5", "4", "java", "c", "sql", "junit",
            "clstr", "1", "4", "python", "c", "java", "bpm",
            "3",
            "opn", "2",
            "ble", "1",
            "mac", "5"
          };
    }

protected:
};

TEST_F(ChromosomeFixture, SomeTest) {
    data::DataHolder dataHolder;
    // Chromosome sut;
}
