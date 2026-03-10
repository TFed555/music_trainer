#include "chordgenerator.h"
#include "../music/pitchutils.h"
#include <random>
#include <QDebug>

ChordGenerator::ChordGenerator(ChordGeneratorParams params)
    : params(params)
{}

GeneratedChord ChordGenerator::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> midiDist(60, 71);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> typeDist(0, params.allowedTypes.size()-1);
    MusicUtils::Chords::ChordType type = params.allowedTypes[typeDist(gen)];

    std::uniform_int_distribution<> inversionDist(0, params.allowedInversions.size()-1);
    MusicUtils::Chords::InversionType inversion = params.allowedInversions[inversionDist(gen)];


    QVector<int> semitones = requiredIntervals[type];
    QVector<int> midiNotes = {firstMidi};
    int lastMidi = firstMidi;
    for (auto i : semitones) {
        lastMidi = 60+((lastMidi-60+i) % 12);
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
    res.desc = QString("%1 -> %2 -> %3").arg(MusicUtils::midiToNote(firstMidi))
                   .arg(MusicUtils::midiToNote(midiNotes[1]))
                   .arg(MusicUtils::midiToNote(midiNotes[2])); //поменять лог

    return res;
}
