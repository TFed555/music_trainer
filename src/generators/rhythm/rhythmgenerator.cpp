#include "rhythmgenerator.h"

RhythmGenerator::RhythmGenerator(RhythmDifficultyConfig config)
    : config(config)
{}

bool countTact(QMap<int, int>& durations, float coef, float &count) {
    if (durations[coef] == 0) {
        return false;
    }
    durations[coef] -= 1;
    count -= (4.0f / coef);
    for (auto k : durations.keys()) {
        if ((4.0f / k) > count) {
            durations[k] = 0;
        }
        else {
            durations[k] = int(count /(4.0f / k));
        }
    }
    return true;
}


GeneratedRhythm RhythmGenerator::generate() {
    // std::uniform_int_distribution<> countDist(config.midiMin, config.midiMax);
    std::uniform_int_distribution<> durationDist(0,config.allowedDurations.size()-1);
    QMap<int, int> durations = {
        { 1, 1 },
        { 2, 2 },
        { 4, 4 },
        { 8, 8 },
        { 16, 16 }
    };

    GeneratedRhythm res;
    float count = config.count;
    while (!std::all_of(durations.begin(), durations.end(),
                       [](int v){ return v == 0; })) {
        Beat beat;
        float coef = config.allowedDurations[durationDist(gen)];
        bool s = countTact(durations, coef, count);
        if (s) {
            beat.duration = coef;
            res.beats.append(beat);
        }
    }
    res.bpm = config.bpm;

    return res;
}
