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
    ChromosomeMatcher (const Chromosome& parent, const Chromosome& descendant)
        : mParent(parent)
        , mDescendant(descendant)
    {}

    void checkIfEveryPersonIsIncluded() const {
        auto descendantIds(getAllPersonIds(mDescendant));
        auto parentIds(getAllPersonIds(mParent));
        std::sort(descendantIds.begin(), descendantIds.end());
        std::sort(parentIds.begin(), parentIds.end());
        ASSERT_THAT(descendantIds, testing::ContainerEq(parentIds));
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
    const Chromosome& mParent;
    const Chromosome& mDescendant;
};

}  // matchers

