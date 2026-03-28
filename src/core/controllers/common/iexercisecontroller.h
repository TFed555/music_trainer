#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"
#include "../../common/models/Difficulty.h"
#include "../../music/musicutils.h"

struct PlaybackLog {
    QDateTime timestamp;
    QString desc;
};

enum class PlaybackendSignal { PlaybackFinished, PlaylistEmpty };

template <typename Config>
const QMap<Difficulty, Config> difficultyMap = {
    {Difficulty::Easy, Config::easy() },
    {Difficulty::Hard, Config::hard() }
};

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

signals:
    void exercisePlayFinished();

public slots:
    virtual void start() { playTone(); };
    virtual void stop() { notePlayer->stop(); };
    virtual void setDifficulty(int level) = 0;

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
                       this, [this]() { onPlaybackFinished(); });
                break;
            case PlaybackendSignal::PlaylistEmpty:
                connect(notePlayer, &NotePlayer::playlistEmpty,
                    this, [this]() { onPlaybackFinished(); });
                break;
        }
    }

protected:
    void log(const QString& desc) {
        playbackLog.append({QDateTime::currentDateTime(), desc});
    }
    virtual void onPlaybackFinished() {
        emit exercisePlayFinished();
    }
protected:
    NotePlayer* notePlayer;
    QVector<PlaybackLog> playbackLog;
};

#endif // IEXERCISECONTROLLER_H
