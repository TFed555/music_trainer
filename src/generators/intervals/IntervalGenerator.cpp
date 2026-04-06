#include "IntervalGenerator.h"
#include "../music/musicutils.h"
#include <QDebug>

IntervalGenerator::IntervalGenerator(IntervalDifficultyConfig config)
    : config(config)
{}

GeneratedInterval IntervalGenerator::generate() {
    std::uniform_int_distribution<> midiDist(config.midiMin, config.midiMax);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> intervalDist(0, config.allowedSemitones.size()-1);
    int semitones = config.allowedSemitones[intervalDist(gen)];

    std::uniform_int_distribution<int> signDist(0, 1);
    int sign = signDist(gen);
    if (sign) semitones = -semitones;

    int secondMidi = firstMidi + semitones;

    while (secondMidi > config.midiMax || secondMidi < config.midiMin) {
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
