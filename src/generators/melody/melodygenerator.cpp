#include "melodygenerator.h"

MelodyGenerator::MelodyGenerator(MelodyDifficultyConfig config)
    : config(config)
{}

GeneratedAudio MelodyGenerator::generate() {
    std::uniform_int_distribution<> midiDist(config.midiMin, config.midiMax);
    GeneratedAudio res;
    QVector<int>& midiNotes = res.midiNotes;
    int current = midiDist(gen);
    midiNotes = {current};
    std::uniform_int_distribution<> intervalDist(0, config.allowedSemitones.size()-1);
    int semitones = config.allowedSemitones[intervalDist(gen)];

    std::uniform_int_distribution<int> signDist(0, 1);
    int sign = signDist(gen);
    if (sign) semitones = -semitones;

    for (int i = 1; i < config.noteCount; i++) {
        int interval = config.allowedSemitones[intervalDist(gen)];
        if (sign) semitones = -semitones;
        current += interval;
        current = std::clamp(current, config.midiMin, config.midiMax);
        midiNotes.append(current);
    }

    while (current > config.midiMax || current < config.midiMin) {
        midiNotes.clear();
        for (int i = 1; i < config.noteCount; i++) {
            int interval = config.allowedSemitones[intervalDist(gen)];
            if (sign) semitones = -semitones;
            current += interval;
            current = std::clamp(current, config.midiMin, config.midiMax);
            midiNotes.append(current);
        }
    }
    res.desc = [](const QVector<int>& midiNotes) -> QString {
        QVector<QString> res;
        res.reserve(midiNotes.size());
        for (const auto& m : midiNotes) {
            res.append(MusicUtils::midiToNote(m));
        }
        return res.join(" ");
    }(midiNotes);
    return res;
}
