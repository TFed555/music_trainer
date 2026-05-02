#include "chordgenerator.h"
#include <QDebug>

ChordGenerator::ChordGenerator(ChordDifficultyConfig config)
    : config(config)
{}

GeneratedChord ChordGenerator::generate() {

    std::uniform_int_distribution<> midiDist(60, 71);

    int firstMidi = midiDist(gen);

    std::uniform_int_distribution<> typeDist(0, config.allowedTypes.size()-1);
    MusicUtils::Chords::ChordType type = config.allowedTypes[typeDist(gen)];

    std::uniform_int_distribution<> inversionDist(0, config.allowedInversions.size()-1);
    MusicUtils::Chords::InversionType inversion = config.allowedInversions[inversionDist(gen)];


    QVector<int> semitones = requiredIntervals[type];
    QVector<int> midiNotes = {firstMidi};
    int lastMidi = firstMidi;
    for (auto i : semitones) {
        lastMidi += i;
        midiNotes.append(lastMidi);
    }

    while (lastMidi > config.midiMax || lastMidi < config.midiMin) {
        midiNotes.clear();
        firstMidi = midiDist(gen);
        lastMidi = firstMidi;
        for (auto i : semitones) {
            lastMidi += i;
            midiNotes.append(lastMidi);
        }
    }

    for (int i = 0; i < (int)inversion; i++) {
        midiNotes[i]+=12;
    }

    std::sort(midiNotes.begin(), midiNotes.end());

    GeneratedChord res;
    res.type = MusicUtils::Chords::chordName(type);
    res.midiNotes = midiNotes;
    res.inversion = MusicUtils::Chords::inversionName(inversion);
    res.root = MusicUtils::midiToNote(midiNotes[1]);
    res.desc = [](const QVector<int>& midiNotes) -> QString {
        QVector<QString> res;
        res.reserve(midiNotes.size());
        for (const auto& m : midiNotes) {
            res.append(MusicUtils::midiToNote(m));
        }
        return res.join(" -> ");
    }(midiNotes);

    return res;
}
