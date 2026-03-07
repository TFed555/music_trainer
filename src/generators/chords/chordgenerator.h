#ifndef CHORDGENERATOR_H
#define CHORDGENERATOR_H

#include "../IGenerator.h"
#include "../../music/pitchutils.h"

struct ChordGeneratorParams {
    QVector<MusicUtils::ChordType> allowedTypes = {
    };
};

inline const QMap<MusicUtils::ChordType, QVector<int>> requiredIntervals = {
    {MusicUtils::ChordType::Major, {4, 3}},
    {MusicUtils::ChordType::Minor, {3, 4}},
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
