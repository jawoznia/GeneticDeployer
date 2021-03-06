#include "../../include/Chromosome.hpp"
#include "../../include/DataHolder.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <algorithm>
#include <memory>

namespace matchers
{

class ChromosomeMatcher {
public:
    ChromosomeMatcher (const Chromosome& descendant)
        : mPeopleIds(getAllPersonIds(descendant))
        , mSolution(descendant.mSolution)
    {
    }

    void checkIfHasSamePeopleAs(const Chromosome& chr) {
        auto chrIds(getAllPersonIds(chr));
        std::sort(chrIds.begin(), chrIds.end());
        std::sort(mPeopleIds.begin(), mPeopleIds.end());
        ASSERT_THAT(mPeopleIds, testing::ContainerEq(chrIds));
    }

    void checkIfSolutionsAreDifferent(const Chromosome& chr) {
        auto chrIds(getAllPersonIds(chr));
        ASSERT_THAT(mPeopleIds, testing::Not(testing::ContainerEq(chrIds)));
    }

    std::vector<std::uint32_t> getAllPersonIds(const Chromosome& chromosome) const {
        std::vector<std::uint32_t> personIds;
        for (const auto& person : chromosome.mDevs) {
            personIds.push_back(person->person_id);
        }
        for (const auto& person : chromosome.mManagers) {
            personIds.push_back(person->person_id);
        }
        for (const auto& row : chromosome.mSolution) {
            for (const auto& gene : row) {
                if (gene.mType != SeatType::Unavailable) {
                    personIds.push_back(gene.mPerson->person_id);
                }
            }
        }
        return personIds;
    }

private:
    std::vector<std::uint32_t> mPeopleIds;
    std::vector<std::vector<Gene>> mSolution;
};

}  // matchers

