#include "noteplayer.h"
#include <QDebug>

NotePlayer::NotePlayer(AudioProcessor* proc, SampleRepository* sampleRepo)
    : processor(proc), sampleRepository{sampleRepo}
{
    connect(processor, &AudioProcessor::playbackStopped,
            this, &NotePlayer::playbackFinished);

    connect(processor, &AudioProcessor::playlistEmpty,
            this, &NotePlayer::playlistEmpty);

    connect(processor, &AudioProcessor::err,
            this, &NotePlayer::error);
}

QVector<float> resample(const QVector<float>& in, double ratio) {
    QVector<float> out((in.size() / ratio) + 1);
    SRC_DATA data {};
    data.data_in = in.data();
    data.input_frames = in.size();
    data.src_ratio = ratio;
    data.data_out = out.data();
    data.output_frames = out.size();
    data.end_of_input = 1;
    int err = src_simple(&data, SRC_SINC_FASTEST, 1);
    if (err) {
        qDebug() << src_strerror(err) ;
    }
    out.resize(data.output_frames_gen);
    return out;
}

void NotePlayer::playMidi(int midi, float durationSec) {
    Sample buffer = sampleRepository->getSample(midi);
    double ratio = std::pow(2.0, (buffer.nearestMidi - midi)/12.0);
    QVector<float> resampledData = resample(buffer.data, ratio);
    buffer.data = resampledData;
    processor->playSample(buffer);
}

void NotePlayer::playExercise(GeneratorType type, int noteCount) {
    GeneratorParams params;

    auto gen = GeneratorFactory::instance()
                   .create(type, params);
    auto result = gen->generate();
    setGenerator(std::move(gen));
    QVector<int> midiNotes = result.midiNotes;
    long size = noteCount > 1 ? midiNotes.size() : midiNotes.size() - 1;
    QVector<Sample> samples;
    double ratio;
    for (size_t i = 0; i < size; i++) {
        Sample buffer = sampleRepository->getSample(midiNotes[i]);
        ratio = std::pow(2.0, (buffer.nearestMidi - midiNotes[i])/12.0);
        QVector<float> resampledData = resample(buffer.data, ratio);
        buffer.data = resampledData;
        samples.append(buffer);
    }
    processor->playGenerated(samples);
    playbackLog.append({QDateTime::currentDateTime(), result.desc});
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    emit notesPlayed(result);
}

void NotePlayer::stop() {
    processor->stopPlayback();
}
