#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"
#include "../../common/models/Difficulty.h"
#include "../../common/models/Attempt.h"
#include "../../music/musicutils.h"
#include "../../../generators/GeneratedAudio.h"

struct PlaybackLog {
    QDateTime timestamp;
    QString desc;
};

enum class PlaybackendSignal { PlaybackFinished, PlaylistEmpty, BeatFinished };

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
    void replayAvailable(int replays);
    void attemptDone(Attempt);
    void setDescription(const QString&);

public slots:
    virtual void start() { generateTask(); };
    virtual void stop() { notePlayer->stop(); };
    virtual void replay() {
            if (replayCount <= 0) return;
            playTask();
            replayCount--;
            emit replayAvailable(replayCount);
    }
    virtual void setDifficulty(int level) = 0;
    void sendDescription() { emit setDescription(description); }

private:
    virtual void generateTask() = 0;
    virtual void playTask() = 0;

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
            case PlaybackendSignal::BeatFinished:
                connect(notePlayer, &NotePlayer::beatFinished,
                        this, [this]() {  });
                break;
        }
    }

protected:
    void log(const QString& desc) {
        playbackLog.append({QDateTime::currentDateTime(), desc});
    }
    virtual void onPlaybackFinished() {
        emit exercisePlayFinished();
        emit replayAvailable(replayCount);
    }
protected:
    NotePlayer* notePlayer;
    QVector<PlaybackLog> playbackLog;
    QString description;
    int replayCount;
};

#endif // IEXERCISECONTROLLER_H
