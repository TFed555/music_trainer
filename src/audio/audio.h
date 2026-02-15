#ifndef AUDIO_H
#define AUDIO_H

#include "RtAudio.h"
#include <QObject>
#include <QVector>
#include <QTime>
#include "generators/IGenerator.h"

#include <memory>

struct PlaybackLog {
    QDateTime timestamp;
    QString desc;
};

class AudioProcessor : public QObject
{

    Q_OBJECT
public:
    AudioProcessor(QObject *parent = nullptr);
    ~AudioProcessor();
    void setGenerator(std::unique_ptr<IGenerator> gen) { generator = std::move(gen);};
    void play(float durationSec);

public slots:
    bool playAudio(const QVector<float>& audioData, double sampleRate);
    void stopPlayback();
signals:
    void playbackFinished();
    void err(const QString& msg);
    void notePlayed(GeneratedAudio& info);
private:
    static int playbackCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                double streamTime, RtAudioStreamStatus status, void *userData);
    void setSampleRate(double sampleRate);
    RtAudio audio;
    std::vector<float> audioBuffer;
    size_t currentFrame = 0;
    bool isPlaying = false;
    std::unique_ptr<IGenerator> generator;
    int sampleRate = 44100;
    QVector<PlaybackLog> playbackLog;
};

#endif // AUDIO_H
