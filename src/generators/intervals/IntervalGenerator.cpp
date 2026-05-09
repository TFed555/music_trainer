#include "IntervalGenerator.h"
#include "../music/musicutils.h"
#include <QDebug>
#include <../core/common/exceptions/GeneratorException.h>

IntervalGenerator::IntervalGenerator(IntervalDifficultyConfig config)
    : config(config)
{}

GeneratedInterval IntervalGenerator::doGenerate() {
    std::uniform_int_distribution<> midiDist(config.midiMin, config.midiMax);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> intervalDist(0, config.allowedSemitones.size()-1);
    int semitones = config.allowedSemitones[intervalDist(gen)];

    std::uniform_int_distribution<int> signDist(0, 1);
    int sign = signDist(gen);
    if (sign) semitones = -semitones;

    int secondMidi = firstMidi + semitones;

    if (secondMidi > config.midiMax || secondMidi < config.midiMin) {
        throw GeneratorException("Midi out of range");
    }
    // int attempts = 0;
    // while (secondMidi > config.midiMax || secondMidi < config.midiMin) {
    //     semitones = config.allowedSemitones[intervalDist(gen)];
    //     secondMidi = firstMidi + semitones;
    // }

    int realSemitones = secondMidi - firstMidi;

    GeneratedInterval res;
    res.direction = realSemitones >= 0
                        ? MusicUtils::Intervals::IntervalDirection::Ascending
                        : MusicUtils::Intervals::IntervalDirection::Descending;
    res.interval.append(MusicUtils::Intervals::semitonesToInterval(std::abs(realSemitones)));
    res.midiNotes.append(firstMidi);
    res.midiNotes.append(secondMidi);
    res.desc = QString("%1 -> %2").arg(MusicUtils::midiToNote(firstMidi)).arg(MusicUtils::midiToNote(secondMidi));

    return res;
}
