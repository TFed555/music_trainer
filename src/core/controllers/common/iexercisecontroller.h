#ifndef IEXERCISECONTROLLER_H
#define IEXERCISECONTROLLER_H

#include <QObject>
#include "../../audio/playback/noteplayer.h"
#include "../../generators/IGenerator.h"

struct PlaybackLog {
    QDateTime timestamp;
    QString desc;
};

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
    virtual void start() { playTone(); };
    virtual void stop() { notePlayer->stop(); };
    // virtual void noteSelected(const QString& name) = 0;
signals:
    void exercisePlayFinished();
private:
    virtual void playTone() = 0;

    void connectPlayer()
    {
        connect(notePlayer, &NotePlayer::playbackFinished,
                this, [] { qDebug() << "Playback finished"; });

        connect(notePlayer, &NotePlayer::error,
                this, [](const QString& msg) { qDebug() << "Error:" << msg; });

        // connect(notePlayer, &NotePlayer::notesPlayed,
        //         this, [this](const GeneratedAudio& result) {
        //             qDebug() << "Played:" << result.desc;
        //             onNotesPlayed(result);
        //         });
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
