#ifndef NOTEPLAYER_H
#define NOTEPLAYER_H
#pragma once

#include "../audio.h"
#include "../core/data/samples/samplerepository.h"
#include "generators/IGenerator.h"
#include "generatorfactory.h"
#include <samplerate.h>

struct PlaybackLog {
    QDateTime timestamp;
    QString desc;
};

class NotePlayer : public QObject
{
    Q_OBJECT
public:
    explicit NotePlayer(AudioProcessor* processor = nullptr, SampleRepository* sampleRepo = nullptr);

    void playMidi(int midi, float durationSec = 0.5f);
    void playExercise(GeneratorType type);
    void stop();
signals:
    void playbackFinished();
    void error(const QString&);
    void notesPlayed(const GeneratedAudio& info);
private:
    void setGenerator(std::unique_ptr<IGenerator> gen) { generator = std::move(gen);};
    AudioProcessor* processor;
    SampleRepository* sampleRepository;
    std::unique_ptr<IGenerator> generator;
    QVector<PlaybackLog> playbackLog;
};

#endif // NOTEPLAYER_H
