//
// Created by Jan Woźniak on 20-Mar-20.
//

#include "../include/Chromosome.hpp"
#include "../include/DataHolder.hpp"
#include "matchers/ChromosomeMatcher.cpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

MATCHER(IsDev, "") { return arg.mPerson != nullptr and arg.mType == SeatType::Developer; }
MATCHER(IsManager, "") { return arg.mPerson != nullptr and arg.mType == SeatType::Manager; }
MATCHER(IsUnavailable, "") { return arg.mPerson == nullptr and arg.mType == SeatType::Unavailable; }

class ChromosomeFixture : public ::testing::Test {
public:
    ChromosomeFixture() {}

    data::DataHolder createDataHolder(const std::vector<std::string>& data)
    {
        data::DataHolder holder;
        holder.SetSeats(data);
        holder.SetDevelopers(data);
        holder.SetManagers(data);
        return holder;
    }

    const std::vector<std::string> properInputData {
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
};

TEST_F(ChromosomeFixture, ShouldCreateProperMapOfSeats) {
    Chromosome sut(createDataHolder(properInputData));
    EXPECT_EQ(sut.mDevs.size(), 6);
    EXPECT_EQ(sut.mManagers.size(), 1);
    const auto& solution(sut.mSolution);

    for (std::uint32_t column = 0; column < solution.size(); ++column)
    {
        EXPECT_THAT(solution[0][column], IsUnavailable());
    }
    EXPECT_THAT(solution[1][0], IsUnavailable());
    EXPECT_THAT(solution[1][2], IsUnavailable());
    EXPECT_THAT(solution[1][3], IsUnavailable());
    EXPECT_THAT(solution[2][0], IsUnavailable());

    EXPECT_THAT(solution[1][1], IsDev());
    EXPECT_THAT(solution[1][4], IsDev());
    EXPECT_THAT(solution[2][1], IsManager());
    EXPECT_THAT(solution[2][2], IsManager());
    EXPECT_THAT(solution[2][3], IsDev());
    EXPECT_THAT(solution[2][4], IsDev());
}

TEST_F(ChromosomeFixture, ShouldHandleEmptyInput) {
    data::DataHolder emptyHolder;
    Chromosome sut(emptyHolder);
    EXPECT_EQ(sut.mDevs.size(), 0);
    EXPECT_EQ(sut.mManagers.size(), 0);
    EXPECT_EQ(sut.mSolution.size(), 0);
}

TEST_F(ChromosomeFixture, ShouldHandleEmptyManagers) {
    std::uint32_t number_of_manager_elements = 7;
    std::vector<std::string> data(properInputData.begin(), properInputData.end() - number_of_manager_elements);
    data.push_back("0");

    Chromosome sut(createDataHolder(data));

    EXPECT_EQ(sut.mDevs.size(), 6);
    EXPECT_EQ(sut.mManagers.size(), 0);
    EXPECT_EQ(sut.mSolution.size(), 3);
}

TEST_F(ChromosomeFixture, ShouldHandleEmptyDevelopers) {
    std::uint32_t number_of_seat_strings = 5;
    std::uint32_t index_of_number_of_managers = 62;
    std::vector<std::string> data(properInputData.begin(), properInputData.begin() + number_of_seat_strings);
    data.push_back("0");
    data.insert(data.end(), properInputData.begin() + index_of_number_of_managers, properInputData.end());

    Chromosome sut(createDataHolder(data));

    EXPECT_EQ(sut.mDevs.size(), 0);
    EXPECT_EQ(sut.mManagers.size(), 1);
    EXPECT_EQ(sut.mSolution.size(), 3);
}

TEST_F(ChromosomeFixture, ShouldHandleEmptySeats) {
    std::uint32_t index_of_last_seat_row = 5;
    std::vector<std::string> data;
    data.push_back("0");
    data.push_back("0");
    data.insert(data.end(), properInputData.begin() + index_of_last_seat_row, properInputData.end());

    Chromosome sut(createDataHolder(data));

    EXPECT_EQ(sut.mDevs.size(), 10);
    EXPECT_EQ(sut.mManagers.size(), 3);
    EXPECT_EQ(sut.mSolution.size(), 0);
}

TEST_F(ChromosomeFixture, DescendantShouldHaveEveryPerson) {
    Chromosome parent1(createDataHolder(properInputData));
    Chromosome parent2(createDataHolder(properInputData));
    EXPECT_EQ(parent1.mDevs.size(), 6);
    EXPECT_EQ(parent1.mManagers.size(), 1);
    EXPECT_EQ(parent2.mDevs.size(), 6);
    EXPECT_EQ(parent2.mManagers.size(), 1);

    Chromosome descendant(parent1, parent2);
    EXPECT_EQ(descendant.mDevs.size(), 6);
    EXPECT_EQ(descendant.mManagers.size(), 1);
    matchers::ChromosomeMatcher descendantMatcher(descendant);
    descendantMatcher.checkIfHasSamePeopleAs(parent1);
}

TEST_F(ChromosomeFixture, MutationShouldNotDeleteAnyData) {
    Chromosome chromosome(createDataHolder(properInputData));
    EXPECT_EQ(chromosome.mDevs.size(), 6);
    EXPECT_EQ(chromosome.mManagers.size(), 1);
    matchers::ChromosomeMatcher chromosomeMatcher(chromosome);

    chromosome.mutate();

    EXPECT_EQ(chromosome.mDevs.size(), 6);
    EXPECT_EQ(chromosome.mManagers.size(), 1);
    chromosomeMatcher.checkIfSolutionsAreDifferent(chromosome);
    chromosomeMatcher.checkIfHasSamePeopleAs(chromosome);
}

