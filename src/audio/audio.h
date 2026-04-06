#ifndef AUDIO_H
#define AUDIO_H

#include "rtaudio/RtAudio.h"
#include <QObject>
#include <QVector>
#include <QTime>
#include "../core/data/samples/sample.h"
#include <memory>

class AudioProcessor : public QObject
{

    Q_OBJECT
    Q_DISABLE_COPY(AudioProcessor)
public:
    AudioProcessor(QObject *parent = nullptr);
    ~AudioProcessor();
    bool playGeneratedNotes(QVector<Sample> samples);
    bool playGeneratedChord(QVector<Sample> samples);
    bool playGeneratedBeat(QVector<Sample> samples);
    void playSample(Sample sample);

public slots:
    bool playAudio(const QVector<float>& audioData, double sampleRate);
    void stopPlayback();
signals:
    void playbackStopped();
    void playbackFinished();
    void err(const QString& msg);
    // void notePlayed();
    void playlistEmpty();
private slots:
    void playNextSample();
private:
    static int playbackCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                double streamTime, RtAudioStreamStatus status, void *userData);
    void setSampleRate(double sampleRate);
    RtAudio audio;
    std::vector<float> audioBuffer;
    size_t currentFrame = 0;
    bool isPlaying = false;
    int sampleRate = 44100;
    QVector<Sample> playlist;
    int playlistIdx = 0;
};

#endif // AUDIO_H
