#include "IntervalGenerator.h"
#include "generatorfactory.h"
#include "../music/pitchutils.h"
#include <random>
#include <QDebug>

namespace {
bool registered = [] {
    GeneratorFactory::instance().registerGenerator(
        GeneratorType::Interval,
        [](GeneratorParams p) {
            return std::make_unique<IntervalGenerator>();
        }
        );
    return true;
}();
}

void forceLinkIntervalGenerator() {}


GeneratedAudio IntervalGenerator::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> midiDist(60, 71);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> intervalDist(1,12);
    int semitones = intervalDist(gen);

    double intervalRatio = std::pow(2.0, semitones/12.0);
    int secondMidi = 60+((firstMidi-60+semitones) % 12);

    int realSemitones = secondMidi - firstMidi;

    GeneratedAudio res;
    res.direction = realSemitones >= 0
                        ? IntervalDirection::Ascending
                        : IntervalDirection::Descending;
    res.interval.append(MusicUtils::semitonesToInterval(std::abs(realSemitones)));
    res.midiNotes.append(firstMidi);
    res.midiNotes.append(secondMidi);
    res.desc = QString("%1 -> %2").arg(MusicUtils::midiToNote(firstMidi)).arg(MusicUtils::midiToNote(secondMidi));

    return res;
}
