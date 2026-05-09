#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"
#include "../../common/models/Difficulty.h"
#include "../../common/models/Attempt.h"
#include "../../common/exceptions/GeneratorException.h"
#include "../../common/exceptions/RecoveryFailedException.h"
#include "../../music/musicutils.h"
#include "../../../generators/GeneratedAudio.h"
#include "../../log/logger.h"

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
    void error(const QString&);

public slots:
    virtual void start() {
        try {
            generateTask();
        } catch(const RecoveryFailedException& e) {
            emit error(e.userMsg);
            Logger::critical(e.what());
        }
    };
    virtual void stop() { notePlayer->stop(); };
    virtual void replay() {
            if (replayCount <= 0) return;
            playTask();
            replayCount--;
            emit replayAvailable(replayCount);
    }
    virtual void setDifficulty(int level) = 0;
    void sendDescription() { emit setDescription(getDescription()); }
    virtual void retranslate() = 0;

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
    virtual QString getDescription() const = 0;
protected:
    NotePlayer* notePlayer;
    QVector<PlaybackLog> playbackLog;
    int replayCount;
};

#endif // IEXERCISECONTROLLER_H
