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


GeneratedAudio IntervalGenerator::generate(int sampleRate, float durationSec) {
    int totalSamples = durationSec * sampleRate;

    QVector<float> buffer;
    buffer.reserve(totalSamples);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> baseFreqDist(130.81, 523.25);

    double baseFreq = baseFreqDist(gen);

    std::uniform_int_distribution<> intervalDist(1,12);
    int semitones = intervalDist(gen);

    double intervalRatio = std::pow(2.0, semitones/12.0);
    double secondFreq = baseFreq * intervalRatio;

    int firstMidiNote = MusicTheory::freqToMidi(baseFreq);
    int secondMidiNote = MusicTheory::freqToMidi(secondFreq);

    double phase = 0.0;

    double inc1 = 2.0 * M_PI * baseFreq / sampleRate;
    for (int i = 0; i < sampleRate; ++i) {
        buffer.append(std::sin(phase));
        phase += inc1;
    }

    int silenceRate = sampleRate * 0.01;
    for (int i = 0; i < silenceRate; ++i) {
        buffer.append(0.0f);
    }

    phase = 0.0;
    double inc2 = 2.0 * M_PI * secondFreq / sampleRate;
    for (int i = 0; i < sampleRate; ++i) {
        buffer.append(std::sin(phase));
        phase += inc2;
    }

    GeneratedAudio res;
    res.samples = buffer;
    res.midiNotes.append(firstMidiNote);
    res.midiNotes.append(secondMidiNote);
    res.desc = QString("%1 -> %2").arg(MusicTheory::midiToNote(firstMidiNote)).arg(MusicTheory::midiToNote(secondMidiNote));

    return res;
}
