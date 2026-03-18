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
    void playNotes(const QVector<int>& midiNotes);
    void playChord(const QVector<int>& midiNotes);
    void playBeat(const GeneratedRhythm& rhythm);
    void stop();
signals:
    void playbackFinished();
    void error(const QString&);
    void playlistEmpty();
private:
    QVector<Sample> loadBeatSamples(const GeneratedRhythm& rhythm);
    QVector<Sample> loadNoteSamples(const QVector<int>& midiNotes);
private:
    AudioProcessor* processor;
    SampleRepository* sampleRepository;
};

#endif // NOTEPLAYER_H
