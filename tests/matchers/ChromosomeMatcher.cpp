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
        : mDescendant(descendant)
    {}

    void checkIfHasSamePeopleAs(const Chromosome& chr) const {
        auto descendantIds(getAllPersonIds(mDescendant));
        auto chrIds(getAllPersonIds(chr));
        std::sort(descendantIds.begin(), descendantIds.end());
        std::sort(chrIds.begin(), chrIds.end());
        ASSERT_THAT(descendantIds, testing::ContainerEq(chrIds));
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
    const Chromosome& mDescendant;
};

}  // matchers

