#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"
#include "../../generators/IGenerator.h"

struct PlaybackLog {
    QDateTime timestamp;
    QString desc;
};

enum class PlaybackendSignal { PlaybackFinished, PlaylistEmpty };

class IExerciseController : public QObject
{
    Q_OBJECT
public:
    explicit IExerciseController(NotePlayer* player,
                                PlaybackendSignal endSignal,
                                QObject *parent = nullptr)
        : QObject(parent)
        , notePlayer(player)
    {
        connectPlayer(endSignal);
    };

public slots:
    virtual void start() { playTone(); };
    virtual void stop() { notePlayer->stop(); };
signals:
    void exercisePlayFinished();
private:
    virtual void playTone() = 0;

    void connectPlayer(PlaybackendSignal endSignal)
    {
        connect(notePlayer, &NotePlayer::playbackFinished,
                this, [] { qDebug() << "Playback finished"; });

        connect(notePlayer, &NotePlayer::error,
                this, [](const QString& msg) { qDebug() << "Error:" << msg; });

        switch(endSignal) {
            case PlaybackendSignal::PlaybackFinished:
                connect(notePlayer, &NotePlayer::playbackFinished,
                       this, [this]() { emit exercisePlayFinished(); });
                break;
            case PlaybackendSignal::PlaylistEmpty:
                connect(notePlayer, &NotePlayer::playlistEmpty,
                    this, [this]() { emit exercisePlayFinished(); });
                break;
        }
    }

protected:
    void log(const QString& desc) {
        playbackLog.append({QDateTime::currentDateTime(), desc});
    }
protected:
    NotePlayer* notePlayer;
    QVector<PlaybackLog> playbackLog;
};

#endif // IEXERCISECONTROLLER_H
