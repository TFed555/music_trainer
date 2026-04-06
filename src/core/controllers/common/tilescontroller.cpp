#include "tilescontroller.h"
#include "../../../music/musicutils.h"

void TilesController::playTile(const QString& noteName) {
    int midi = MusicUtils::noteToMidi(noteName);
    notePlayer->playMidi(midi);
}
