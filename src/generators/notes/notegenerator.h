#ifndef NOTEGENERATOR_H
#define NOTEGENERATOR_H
#pragma once

#include "../IGenerator.h"
#include "../core/common/models/Difficulty.h"
#include <random>

class NoteGenerator : public IGenerator<NoteGenerator, GeneratedAudio>
{
public:
    explicit NoteGenerator(NoteDifficultyConfig config = {});
    GeneratedAudio generate();
private:
    std::mt19937 gen{std::random_device{}()};
    NoteDifficultyConfig config;
};

#endif // NOTEGENERATOR_H
