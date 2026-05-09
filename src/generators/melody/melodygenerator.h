#ifndef MELODYGENERATOR_H
#define MELODYGENERATOR_H

#include "../GeneratedAudio.h"
#include "../IGenerator.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class MelodyGenerator : public IGenerator<MelodyGenerator, GeneratedAudio>
{
    friend class IGenerator<MelodyGenerator, GeneratedAudio>;
public:
    explicit MelodyGenerator(MelodyDifficultyConfig config = {});
    // GeneratedAudio generate();
protected:
    GeneratedAudio doGenerate() override;
private:
    std::mt19937 gen{std::random_device{}()};
    MelodyDifficultyConfig config;
};

#endif // MELODYGENERATOR_H
