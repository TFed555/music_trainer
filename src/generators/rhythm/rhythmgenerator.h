#ifndef RHYTHMGENERATOR_H
#define RHYTHMGENERATOR_H

#include "../IGenerator.h"
#include "../generatedrhythm.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class RhythmGenerator : public IGenerator<GeneratedRhythm>
{
public:
    explicit RhythmGenerator(RhythmDifficultyConfig config = {});
    GeneratedRhythm generate() override;
private:
    std::mt19937 gen{std::random_device{}()};
    RhythmDifficultyConfig config;
};

#endif // RHYTHMGENERATOR_H
