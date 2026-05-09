#ifndef NOTEGENERATOR_H
#define NOTEGENERATOR_H
#pragma once

#include "../GeneratedAudio.h"
#include "../IGenerator.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class NoteGenerator : public IGenerator<NoteGenerator, GeneratedAudio>
{
    friend class IGenerator<NoteGenerator, GeneratedAudio>;
public:
    explicit NoteGenerator(NoteDifficultyConfig config = {});
    // GeneratedAudio generate();
protected:
    GeneratedAudio doGenerate() override;
private:
    std::mt19937 gen{std::random_device{}()};
    NoteDifficultyConfig config;
};

#endif // NOTEGENERATOR_H
