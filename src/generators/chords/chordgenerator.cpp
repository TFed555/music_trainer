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
    std::uniform_real_distribution<> midiDist(60, 71);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> typeDist(0, params.allowedTypes.size()-1);
    MusicUtils::ChordType type = params.allowedTypes[typeDist(gen)];

    QVector<int> semitones = requiredIntervals[type];
    QVector<int> midiNotes = {firstMidi};
    int lastMidi = firstMidi;
    for (auto i : semitones) {
        lastMidi = 60+((lastMidi-60+i) % 12);
        midiNotes.append(lastMidi);
    }

    GeneratedChord res;
    res.type = MusicUtils::chordTypeNames[type];
    res.midiNotes = midiNotes;
    res.desc = QString("%1 -> %2 -> %3").arg(MusicUtils::midiToNote(firstMidi))
                   .arg(MusicUtils::midiToNote(midiNotes[1]))
                   .arg(MusicUtils::midiToNote(midiNotes[2])); //поменять лог

    return res;
}
