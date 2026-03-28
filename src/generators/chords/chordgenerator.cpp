#include "chordgenerator.h"
#include <QDebug>

ChordGenerator::ChordGenerator(ChordDifficultyConfig config)
    : config(config)
{}

GeneratedChord ChordGenerator::generate() {

    std::uniform_int_distribution<> midiDist(60, 71);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> typeDist(0, config.allowedTypes.size()-1);
    MusicUtils::Chords::ChordType type = config.allowedTypes[typeDist(gen)];

    std::uniform_int_distribution<> inversionDist(0, config.allowedInversions.size()-1);
    MusicUtils::Chords::InversionType inversion = config.allowedInversions[inversionDist(gen)];


    QVector<int> semitones = requiredIntervals[type];
    QVector<int> midiNotes = {firstMidi};
    int lastMidi = firstMidi;
    for (auto i : semitones) {
        lastMidi += i;
        // lastMidi = 60+((lastMidi-60+i) % 12);
        midiNotes.append(lastMidi);
    }

    for (int i = 0; i < (int)inversion; i++) {
        midiNotes[i]+=12;
    }

    std::sort(midiNotes.begin(), midiNotes.end());

    GeneratedChord res;
    res.type = MusicUtils::Chords::chordTypeNames[type];
    res.midiNotes = midiNotes;
    res.inversion = MusicUtils::Chords::inversionNames[inversion];
    res.root = MusicUtils::midiToNote(midiNotes[1]);
    res.desc = QString("%1 -> %2 -> %3").arg(MusicUtils::midiToNote(midiNotes[0]))
                   .arg(MusicUtils::midiToNote(midiNotes[1]))
                   .arg(MusicUtils::midiToNote(midiNotes[2])); //поменять лог

    return res;
}
