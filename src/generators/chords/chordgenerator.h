#ifndef CHORDGENERATOR_H
#define CHORDGENERATOR_H

#include "../IGenerator.h"
#include "../../music/pitchutils.h"

struct ChordGeneratorParams {
    QVector<MusicUtils::Chords::ChordType> allowedTypes = {
        MusicUtils::Chords::ChordType::Major,
        MusicUtils::Chords::ChordType::Minor
};
    QVector<MusicUtils::Chords::InversionType> allowedInversions = {
        MusicUtils::Chords::InversionType::Root,
        MusicUtils::Chords::InversionType::First,
        MusicUtils::Chords::InversionType::Second
};
};

inline const QMap<MusicUtils::Chords::ChordType, QVector<int>> requiredIntervals = {
    {MusicUtils::Chords::ChordType::Major, {4, 3}},
    {MusicUtils::Chords::ChordType::Minor, {3, 4}},
};

class ChordGenerator : public IGenerator<GeneratedChord>
{
public:
    explicit ChordGenerator(ChordGeneratorParams);
    GeneratedChord generate() override;
private:
    ChordGeneratorParams params;
};

#endif // CHORDGENERATOR_H
