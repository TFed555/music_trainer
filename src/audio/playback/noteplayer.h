#ifndef NOTEPLAYER_H
#define NOTEPLAYER_H
#pragma once

#include "../audio.h"
#include "../core/data/samples/samplerepository.h"
#include <samplerate.h>
#include "../../generators/generatedrhythm.h"

class NotePlayer : public QObject
{
    Q_OBJECT
public:
    explicit NotePlayer(AudioProcessor* processor = nullptr, SampleRepository* sampleRepo = nullptr);

    void playMidi(int midi, float durationSec = 0.5f);
    void playMetronome(const GeneratedRhythm& rhythm);
    void playNotes(const QVector<int>& midiNotes);
    void playChord(const QVector<int>& midiNotes);
    void playBeat(const GeneratedRhythm& rhythm);
    void stop();
signals:
    void playbackFinished();
    void error(const QString&);
    void playlistEmpty();
    void beatFinished();
    void metronomeFinished();
private:
    QVector<Sample> loadBeatSamples(const QVector<Beat>& beats, const int bpm);
    QVector<Sample> loadNoteSamples(const QVector<int>& midiNotes);
    template <typename Sender, typename Signal, typename Receiver, typename Slot>
    void connectOnce(Sender* s, Signal sig, Receiver r, Slot slot) {
        QMetaObject::Connection* conn = new QMetaObject::Connection;
        *conn = QObject::connect(s, sig, r, [r, slot, conn] {
            (r->*slot)();
            QObject::disconnect(*conn);
            delete conn;
        });
    };
private:
    AudioProcessor* processor;
    SampleRepository* sampleRepository;
    Sample accentSample = sampleRepository->getBeatSample(0);
    Sample ordinarySample = sampleRepository->getBeatSample(1);
    Sample userBeatSample = sampleRepository->getBeatSample(2);
};

#endif // NOTEPLAYER_H
