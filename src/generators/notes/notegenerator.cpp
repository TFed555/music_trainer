#include "notegenerator.h"
#include <QDebug>

NoteGenerator::NoteGenerator(NoteDifficultyConfig config)
    : config(config)
{}

GeneratedAudio NoteGenerator::generate() {
    std::uniform_int_distribution<> midiDist(config.midiMin, config.midiMax);

    int midi = midiDist(gen);

    GeneratedAudio res;
    res.midiNotes.append(midi);
    res.desc = QString("%1").arg(MusicUtils::midiToNote(midi));

    return res;
}
