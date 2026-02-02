#include "audio.h"
#include <QDebug>

AudioProcessor::AudioProcessor(QObject *parent) : QObject(parent){}

AudioProcessor::~AudioProcessor() {
    stopPlayback();
}

void AudioProcessor::play(float durationSec) {
    if (!generator) return;
    // setSampleRate();
    auto result = generator->generate(sampleRate, durationSec);
    playAudio(result.samples, sampleRate);
    playbackLog.append({QDateTime::currentDateTime(), result.desc});
    emit notePlayed(result.desc);
}

bool AudioProcessor::playAudio(const QVector<float>& m_audioData, double sampleRate)
{
    stopPlayback();

    if (m_audioData.isEmpty()) {
        emit err("Audio data is empty");
        return false;
    }

    if (audio.getDeviceCount() < 1) {
        emit err("No audio devices found");
        return false;
    }

    audioBuffer.clear();
    audioBuffer.reserve(m_audioData.size());
    for (const float& sample : m_audioData) {
        audioBuffer.push_back(sample);
    }

    currentFrame = 0;

    RtAudio::StreamParameters parameters;
    parameters.deviceId = audio.getDefaultOutputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;

    unsigned int bufferFrames = 512;

    try {
        audio.openStream(&parameters, nullptr, RTAUDIO_FLOAT32,
                          static_cast<unsigned int>(sampleRate),
                          &bufferFrames, &AudioProcessor::playbackCallback, this);
        audio.startStream();
        isPlaying = true;

        qDebug() << "Playback started frames " << audioBuffer.size();
        return true;
    }
    catch (RtAudioError& e) {
        emit err(QString("Audio error %1").arg(e.getMessage().c_str()));
        return false;
    }
}

int AudioProcessor::playbackCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                            double streamTime, RtAudioStreamStatus status, void *userData) {
    AudioProcessor* processor = static_cast<AudioProcessor*>(userData);

    float* buffer = static_cast<float*>(outputBuffer);
    size_t framesToCopy = nBufferFrames;

    if (!processor || processor->audioBuffer.empty()) {
        std::fill(buffer, buffer + nBufferFrames, 0.0f);
        return 1;
    }

    if (processor->currentFrame + framesToCopy > processor->audioBuffer.size()) {
        framesToCopy = processor->audioBuffer.size() - processor->currentFrame;
    }

    if (framesToCopy > 0) {
        const float* source = processor->audioBuffer.data() + processor->currentFrame;
        std::copy(source, source + framesToCopy, buffer);
        processor->currentFrame += framesToCopy;


        if (framesToCopy < nBufferFrames) {
            std::fill(buffer + framesToCopy, buffer + nBufferFrames, 0.0f);
        }
    } else {
        std::fill(buffer, buffer + nBufferFrames, 0.0f);

        QMetaObject::invokeMethod(processor, "stopPlayback", Qt::QueuedConnection);
    }

    return 0;
}

void AudioProcessor::stopPlayback() {
    if (isPlaying) {
        try {
            if (audio.isStreamOpen()) {
                audio.stopStream();
            }
            if (audio.isStreamOpen()) {
                audio.closeStream();
            }
            isPlaying = false;
            audioBuffer.clear();
            currentFrame = 0;

            emit playbackFinished();
            qDebug() << "Playback stopped";
        }
        catch(RtAudioError &e) {
            emit err(QString("error stoping audio %1").arg(e.getMessage().c_str()));
        }
    }
}
