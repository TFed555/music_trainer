#include "chordgenerator.h"
#include "../music/pitchutils.h"
#include <random>
#include <QDebug>

GeneratedChord ChordGenerator::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> midiDist(60, 71);

    int firstMidi = midiDist(gen);

    // std::uniform_int_distribution<> intervalDist(1,12);
    // int semitones = intervalDist(gen);

    int secondMidi = 60+((firstMidi-60+3) % 12); //пока что только мажор

    int thirdMidi = 60+((secondMidi-60+2) % 12);

    // int realSemitones = secondMidi - firstMidi;

    GeneratedChord res;
    // res.chordName = MusicUtils::notesToChord()
    res.tone = "мажор";
    res.midiNotes.append(firstMidi);
    res.midiNotes.append(secondMidi);
    res.midiNotes.append(thirdMidi);
    res.desc = QString("%1 -> %2 -> %3").arg(MusicUtils::midiToNote(firstMidi))
                   .arg(MusicUtils::midiToNote(secondMidi))
                   .arg(MusicUtils::midiToNote(thirdMidi));

    return res;
}
