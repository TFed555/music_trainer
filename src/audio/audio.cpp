#include "audio.h"
#include <QDebug>
#include <QTimer>

AudioProcessor::AudioProcessor(QObject *parent) : QObject(parent){}

AudioProcessor::~AudioProcessor() {
    stopPlayback();
}

bool AudioProcessor::playGeneratedNotes(QVector<Sample> samples) {
    if (samples.isEmpty()) return false;
    playlist = samples;
    playlistIdx = 0;
    connect(this, &AudioProcessor::playbackStopped,
            this, &AudioProcessor::playNextSample,
            Qt::UniqueConnection);

    playNextSample();
    return true;
}

bool AudioProcessor::playGeneratedChord(QVector<Sample> samples) {
    if (samples.isEmpty()) return false;
    int maxSampleLen = 0;
    for (auto s : samples) {
        maxSampleLen = qMax(maxSampleLen, s.data.size());
    }
    QVector<float> audioData(maxSampleLen, 0.0f);
    for (auto& s : samples) {
        for (size_t i = 0; i < s.data.size(); i++){
            audioData[i] += s.data[i];
        }
    }

    playAudio(audioData, sampleRate);
    return true;
}

bool AudioProcessor::playGeneratedBeat(QVector<Sample> samples) {
    if (samples.isEmpty()) return false;
    int len = 0;
    int offset = 0;
    for (auto s : samples) {
        int delay = (s.delayms/1000.0) * sampleRate;
        offset += delay;
        len = qMax(len, offset + (int)s.data.size());
    }
    // len+=samples.last().data.size();
    offset = 0;
    QVector<float> audioData(len, 0.0f);
    for (auto& s : samples) {
        int delay = (s.delayms/1000.0) * sampleRate;

        for (size_t i = 0; i < s.data.size(); i++){
            int idx = i + offset;
            if (idx < audioData.size()) {
                audioData[idx] += s.data[i];
            }
        }
        offset += delay;
    }

    playAudio(audioData, sampleRate);
    return true;
}

void AudioProcessor::playNextSample() {
    if (playlistIdx >= playlist.size()) {
        disconnect(this, &AudioProcessor::playbackStopped,
                   this, &AudioProcessor::playNextSample);
        emit playlistEmpty();
        return;
    }
    Sample s = playlist[playlistIdx++];
    QTimer::singleShot(s.delayms, this, [this, s]() {
        playAudio(s.data, s.sampleRate);
    });
}

void AudioProcessor::playSample(Sample sample) {
    playAudio(sample.data, sample.sampleRate);
}

bool AudioProcessor::playAudio(const QVector<float>& m_audioData, double sampleRate)
{
    stopPlayback();

    if (m_audioData.isEmpty()) {
        emit err("Audio data is empty");
        return false;
    }

    if (audio.getDeviceCount() < 1) {
        emit err("No audio devices");
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

            emit playbackStopped();
            qDebug() << "Playback stopped";
        }
        catch(RtAudioError &e) {
            emit err(QString("error stoping audio %1").arg(e.getMessage().c_str()));
        }
    }
}
