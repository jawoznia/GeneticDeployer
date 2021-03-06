//
// Created by Jan Woźniak on 21-Mar-20.
//

#include "../include/GeneticDeployer.hpp"

#include "../include/helpers/Printers.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <sstream>
#include <ios>

GeneticDeployer::GeneticDeployer(const std::string& filename)
    : mFileReader(std::make_unique<data::FileReader>(filename))
    , mFileExporter(std::make_unique<data::FileExporter>("CalculatedPerformance.txt"))
    , mFitnessToOccurance(std::make_pair(0, 0))
    , mFileName(filename)
    , mGeneration(0)
    , mMt(mRd())
{
}

void GeneticDeployer::start() {
    init();
    calculate();
    saveScoreToFile((*mSolutions.begin())->mFitness);
}

void GeneticDeployer::init() {
    mStartTime = std::chrono::system_clock::now();
    mDataHolder = mFileReader->LoadData();
    initPopulation();
}

void GeneticDeployer::initPopulation()
{
    mSolutions.resize(mSizeOfPopulation);
    for (auto& solution : mSolutions)
    {
        solution = std::make_unique<Chromosome>(*mDataHolder);
    }
}

void GeneticDeployer::calculate()
{
    std::cout << __func__ << " starts.\n";
    while (not shouldEnd()) {
        crossover();
        mutation();
        calculateFitness();
        printBest();
    }
}

void GeneticDeployer::crossover()
{
    const auto ids = tournamentSelection();
    std::vector<std::unique_ptr<Chromosome>> descendants(mNumberOfDescendants);

    descendants[0] = std::make_unique<Chromosome>(*mSolutions[*ids.begin()], *mSolutions[*ids.rbegin()]);
    for (std::uint32_t i = 1; i < mNumberOfDescendants; ++i)
    {
        descendants[i] = std::make_unique<Chromosome>(*mSolutions[ids[i - 1]], *mSolutions[ids[i]]);
    }
    getMostSuited();
    mSolutions.insert(mSolutions.end(),
        std::make_move_iterator(descendants.begin()),
        std::make_move_iterator(descendants.end()));
}

std::vector<std::uint32_t> GeneticDeployer::tournamentSelection()
{
    std::vector<std::uint32_t> winningIds(mNumberOfDescendants);
    std::uniform_int_distribution<> dis(0, mSizeOfPopulation - 1);
    for (auto& winningId : winningIds)
    {
        const static std::uint32_t sizeOfSingleTournament = 5;
        std::vector<std::uint32_t> ids(sizeOfSingleTournament);
        for (auto& id : ids)
        {
            id = dis(mMt);
        }
        winningId = getMostFitnessSolutionId(ids);
    }
    return winningIds;
}

std::uint32_t GeneticDeployer::getMostFitnessSolutionId(const std::vector<std::uint32_t>& ids)
{
    std::uint32_t maxVal = std::numeric_limits<std::uint32_t>::min();
    std::uint32_t bestId = ids[0];
    for (const auto id : ids)
    {
        auto currentFitness = mSolutions[id]->getFitness();
        if (maxVal < currentFitness)
        {
            bestId = id;
            maxVal = currentFitness;
        }
    }
    return bestId;
}

void GeneticDeployer::mutation() {
    static constexpr float mutationProbabilityRatio{0.15};
    std::uniform_real_distribution<> mutationProbabilityDis(0, 1);
    for (const auto& solution : mSolutions) {
        if (mutationProbabilityDis(mMt) < mutationProbabilityRatio) {
            solution->mutate();
        }
    }
}

void GeneticDeployer::calculateFitness() {
    for (const auto& solution : mSolutions) {
        solution->calculateFitness();
    }
}

void GeneticDeployer::getMostSuited() {
    static std::uint32_t numberOfParentsToNextGeneration = mSizeOfPopulation - mNumberOfDescendants;
    sort();
    mSolutions.erase(mSolutions.begin() + numberOfParentsToNextGeneration, mSolutions.end());
}

void GeneticDeployer::sort() {
    std::ranges::sort(mSolutions,
        [](const auto& chr1, const auto& chr2) {
            return chr1->mFitness > chr2->mFitness;
        });
}

void GeneticDeployer::printBest() {
    const auto& currentBest{std::ranges::max_element(mSolutions,
        [](const auto& chr1, const auto& chr2) { return chr1->mFitness < chr2->mFitness;})};
    std::cout << "; Current best fitness " << (*currentBest)->mFitness << "\n";
}

void GeneticDeployer::checkIfAnySolutionHasDuplicates() {
    for (const auto& solution : mSolutions) {
        if (solution->hasDuplicates()) {
            throw std::runtime_error("Duplicate found. Stopping program!");
        }
    }
}

bool GeneticDeployer::shouldEnd() {
    return isDurationTooLong() or isFitnessPeakFound() or isMaxGenerationReached();
}

bool GeneticDeployer::isDurationTooLong()
{
    static constexpr auto five_minutes{std::chrono::seconds(300)};
    const auto currentTime{std::chrono::system_clock::now()};
    const auto secondsSinceStart{std::chrono::duration_cast<std::chrono::seconds>(
        currentTime - mStartTime).count()};
    std::cout << "Running for " << secondsSinceStart << " seconds; ";
    return secondsSinceStart > five_minutes.count();
}

bool GeneticDeployer::isFitnessPeakFound()
{
    const auto& currentBestFitness = (*mSolutions.begin())->mFitness;
    if (mFitnessToOccurance.first == currentBestFitness) {
        if ((++mFitnessToOccurance.second) == mOccurancesToStopProgram) {
            std::cout << "Fitness didn't change since " << mOccurancesToStopProgram
                << ". Stopping program.\n";
            return true;
        }
    } else {
        mFitnessToOccurance = std::make_pair(currentBestFitness, 1);
    }
    return false;
}

bool GeneticDeployer::isMaxGenerationReached()
{
    static constexpr std::uint32_t numberOfGenerations = 100;
    if (mGeneration++ == numberOfGenerations) {
        std::cout << "Stopping due to generation limit\n";
        return true;
    } else {
        std::cout << "Generation " << mGeneration << "; ";
        return false;
    }
}

void GeneticDeployer::saveScoreToFile(std::uint32_t fitness) {
    std::stringstream scoreToSave;
    scoreToSave << mFileName
                << "\nSize_of_pop " << mSizeOfPopulation
                << "\noccurances " << mOccurancesToStopProgram
                << "\nselections " << mNumberOfDescendants
                << "\nFitness " << fitness
                << "\nTime " << getElapsedTime().count() << "s";
    mFileExporter->appendData(scoreToSave.str());
}

std::chrono::duration<double> GeneticDeployer::getElapsedTime() {
    return std::chrono::system_clock::now() - mStartTime;
}

void GeneticDeployer::setSizeOfPopulation(std::uint32_t sizeOfPopulation)
{
    mSizeOfPopulation = sizeOfPopulation;
}

void GeneticDeployer::setOccurancesToStopProgram(std::uint32_t occurancesToStopProgram)
{
    mOccurancesToStopProgram = occurancesToStopProgram;
}

void GeneticDeployer::setNumberOfDescendants(std::uint32_t numberOfDescendants)
{
    mNumberOfDescendants = numberOfDescendants;
}

