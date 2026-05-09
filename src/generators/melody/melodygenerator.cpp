#include "melodygenerator.h"

MelodyGenerator::MelodyGenerator(MelodyDifficultyConfig config)
    : config(config)
{}

GeneratedAudio MelodyGenerator::doGenerate() {
    std::uniform_int_distribution<> midiDist(config.midiMin, config.midiMax);
    std::uniform_int_distribution<> intervalDist(0, config.allowedSemitones.size() - 1);
    std::uniform_int_distribution<> directionDist(0, config.directions.size()-1);
    std::uniform_int_distribution<int> signDist(0, 1);

    int dir = directionDist(gen);
    int sign = 0;
    bool wavy = false;
    switch(dir){
        case 0:
            sign = 0;
            break;
        case 1:
            sign = 1;
            break;
        case 2:
            wavy = true;
            break;
    }

    GeneratedAudio res;
    res.midiNotes.reserve(config.noteCount);

    int current = midiDist(gen);
    res.midiNotes.append(current);

    for (int i = 1; i < config.noteCount; i++) {
        int interval = config.allowedSemitones[intervalDist(gen)];
        if (i == config.noteCount/2 && wavy) {
            sign = 1;
        }
        if (sign) interval = -interval;
        current = std::clamp(current + interval, config.midiMin, config.midiMax);
        res.midiNotes.append(current);
    }

    QVector<QString> names;
    names.reserve(res.midiNotes.size());
    for (int m : res.midiNotes)
        names.append(MusicUtils::midiToNote(m));
    res.desc = names.join(" ");
    res.direction = MusicUtils::melodyDirNames[config.directions[dir]];

    return res;
}
