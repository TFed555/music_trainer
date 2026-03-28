#ifndef RHYTHMGENERATOR_H
#define RHYTHMGENERATOR_H

#include "../IGenerator.h"
#include "../generatedrhythm.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class RhythmGenerator : public IGenerator<RhythmGenerator, GeneratedRhythm>
{
public:
    explicit RhythmGenerator(RhythmDifficultyConfig config = {});
    GeneratedRhythm generate();
private:
    std::mt19937 gen{std::random_device{}()};
    RhythmDifficultyConfig config;
};

#endif // RHYTHMGENERATOR_H
