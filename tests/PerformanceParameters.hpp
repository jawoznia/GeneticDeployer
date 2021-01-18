#include <cstdint>
#include <string>
#include <vector>

namespace data
{

struct PerformanceParameters {
    PerformanceParameters(const std::string& fileName, std::uint32_t sizeOfPopulation,
        std::uint32_t numberOfSelections, std::uint8_t occurancesToStopProgram)
        : fileName(fileName)
        , sizeOfPopulation(sizeOfPopulation)
        , numberOfSelections(numberOfSelections)
        , occurancesToStopProgram(occurancesToStopProgram)
    {}

public:
    std::string fileName;

    std::uint32_t sizeOfPopulation;
    std::uint32_t numberOfSelections;
    std::uint8_t occurancesToStopProgram;
};

inline std::vector<PerformanceParameters> getPerformanceParameters() {
    std::vector<PerformanceParameters> performanceParameters;
    performanceParameters.emplace_back("../data/a_solar.txt", 50, 40, 10);
    performanceParameters.emplace_back("../data/a_solar.txt", 100, 80, 10);
    performanceParameters.emplace_back("../data/a_solar.txt", 150, 120, 10);
    performanceParameters.emplace_back("../data/a_solar.txt", 200, 160, 10);

    return performanceParameters;
}

}

