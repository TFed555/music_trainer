#ifndef CHORDGENERATOR_H
#define CHORDGENERATOR_H
#pragma once

#include "../GeneratedAudio.h"
#include "../IGenerator.h"
#include <random>
#include "../core/common/models/Difficulty.h"

inline const QMap<MusicUtils::Chords::ChordType, QVector<int>> requiredIntervals = {
    {MusicUtils::Chords::ChordType::Major, {4, 3}},
    {MusicUtils::Chords::ChordType::Minor, {3, 4}},
    {MusicUtils::Chords::ChordType::MajorSeventhChord, {4, 3, 3}},
    {MusicUtils::Chords::ChordType::MinorSeventhChord, {3, 4, 3}},
    {MusicUtils::Chords::ChordType::AugmentedTriad, {4, 4}},
    {MusicUtils::Chords::ChordType::DiminishedTriad, {3, 3}}
};

class ChordGenerator : public IGenerator<ChordGenerator, GeneratedChord>
{
    friend class IGenerator<ChordGenerator, GeneratedChord>;
public:
    explicit ChordGenerator(ChordDifficultyConfig config = {});
protected:
    GeneratedChord doGenerate() override;
private:
    ChordDifficultyConfig config;
    std::mt19937 gen{std::random_device{}()};
};

#endif // CHORDGENERATOR_H
