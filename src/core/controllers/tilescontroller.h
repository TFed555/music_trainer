#ifndef TILESCONTROLLER_H
#define TILESCONTROLLER_H

#include "../audio/playback/noteplayer.h"

struct Note {
    QString name;
    int midi;
};

class TilesController
{
public:
    explicit TilesController() {};
    QVector<Note> setNotes();
public slots:
    void playTile(const QString& noteName);
private:
    NotePlayer* notePlayer;
};

#endif // TILESCONTROLLER_H
