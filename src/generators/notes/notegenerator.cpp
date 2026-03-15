#include "notegenerator.h"
#include <QDebug>

NoteGenerator::NoteGenerator(NoteDifficultyConfig config)
    : config(config)
{}

GeneratedAudio NoteGenerator::generate() {
    std::uniform_int_distribution<> midiDist(config.midiMin, config.midiMax);
    GeneratedAudio res;
    QVector<int>& midiNotes = res.midiNotes;
    int size = config.noteCount > 1 ? config.noteCount - 1 : config.noteCount;
    for (int i = 0; i < size; i++) {
        midiNotes.append(midiDist(gen));
    }
    if (config.noteCount>1) {
        std::uniform_int_distribution<> lastMidiDist(0, 1);
        int lastMidi = lastMidiDist(gen) == 1 ? midiNotes[0] : midiDist(gen);
        midiNotes.append(lastMidi);
    }
    res.desc="";
    for (int j : midiNotes) {
        res.desc += QString("%1 ").arg(MusicUtils::midiToNote(j));
    }

    return res;
}
