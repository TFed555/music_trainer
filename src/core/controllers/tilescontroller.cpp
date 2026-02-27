#include "tilescontroller.h"
#include "../../music/pitchutils.h"

void TilesController::playTile(const QString& noteName) {
    int midi = MusicTheory::noteToMidi(noteName);
    notePlayer->playMidi(midi);
}

QVector<Note> TilesController::setNotes() {
    QVector<Note> notes;
    notes.resize(12);
    for (int i = 0; i < notes.size(); i++) {
        notes[i].name = MusicTheory::noteNames[i];
    }
    return notes;
}
