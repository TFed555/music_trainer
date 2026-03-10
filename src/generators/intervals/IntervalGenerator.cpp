#include "IntervalGenerator.h"
#include "../music/pitchutils.h"
#include <QDebug>

GeneratedInterval IntervalGenerator::generate() {
    std::uniform_real_distribution<> midiDist(48, 83);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> intervalDist(-12,12);
    int semitones = intervalDist(gen);

    int secondMidi = firstMidi + semitones;

    while (secondMidi > 83 || secondMidi < 48) {
        semitones = intervalDist(gen);
        secondMidi = firstMidi + semitones;
    }

    int realSemitones = secondMidi - firstMidi;

    GeneratedInterval res;
    res.direction = realSemitones >= 0
                        ? IntervalDirection::Ascending
                        : IntervalDirection::Descending;
    res.interval.append(MusicUtils::Intervals::semitonesToInterval(std::abs(realSemitones)));
    res.midiNotes.append(firstMidi);
    res.midiNotes.append(secondMidi);
    res.desc = QString("%1 -> %2").arg(MusicUtils::midiToNote(firstMidi)).arg(MusicUtils::midiToNote(secondMidi));

    return res;
}
