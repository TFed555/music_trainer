#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"

class IExerciseController : public QObject
{
    Q_OBJECT
public:
    explicit IExerciseController(NotePlayer* player, QObject *parent = nullptr)
        : QObject(parent)
        , notePlayer(player)
    {
        connectPlayer();
    };

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
private:
    virtual void playTone() = 0;

    virtual void onNotesPlayed(const GeneratedAudio& result) = 0;

    void connectPlayer()
    {
        connect(notePlayer, &NotePlayer::playbackFinished,
                this, [] { qDebug() << "Playback finished"; });

        connect(notePlayer, &NotePlayer::error,
                this, [](const QString& msg) { qDebug() << "Error:" << msg; });

        connect(notePlayer, &NotePlayer::notesPlayed,
                this, [this](const GeneratedAudio& result) {
                    qDebug() << "Played:" << result.desc;
                    onNotesPlayed(result);
                });
    }
protected:

    NotePlayer* notePlayer;
};

#endif // IEXERCISECONTROLLER_H
