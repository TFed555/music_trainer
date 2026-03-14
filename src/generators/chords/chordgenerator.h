#ifndef CHORDGENERATOR_H
#define CHORDGENERATOR_H
#pragma once

#include "../IGenerator.h"
#include <random>
#include "../core/common/models/Difficulty.h"

inline const QMap<MusicUtils::Chords::ChordType, QVector<int>> requiredIntervals = {
    {MusicUtils::Chords::ChordType::Major, {4, 3}},
    {MusicUtils::Chords::ChordType::Minor, {3, 4}},
};

class ChordGenerator : public IGenerator<GeneratedChord>
{
public:
    explicit ChordGenerator(ChordDifficultyConfig config = {});
    GeneratedChord generate() override;
private:
    ChordDifficultyConfig config;
    std::mt19937 gen{std::random_device{}()};
};

#endif // CHORDGENERATOR_H
