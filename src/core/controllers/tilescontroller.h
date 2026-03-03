#ifndef TILESCONTROLLER_H
#define TILESCONTROLLER_H

#include "../audio/playback/noteplayer.h"

class TilesController : public QObject
{
    Q_OBJECT
public:
    explicit TilesController(NotePlayer* player,  QObject *parent = nullptr) : notePlayer(player) {};
public slots:
    void playTile(const QString& noteName);
private:
    NotePlayer* notePlayer;
};

#endif // TILESCONTROLLER_H
