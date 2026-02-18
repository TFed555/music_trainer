#include "noteplayer.h"
#include <QDebug>
#include "../dsp/oscillator.h"
#include "../../music/pitchutils.h"

NotePlayer::NotePlayer(AudioProcessor* proc) : processor(proc) {}

float envelope(int sample, int totalSamples) {
    float t = float(sample) / totalSamples;
    return std::exp(-5.0f * t); // экспоненциальный спад
}


void NotePlayer::playMidi(int midi, float durationSec) {
    double freq = MusicTheory::midiToFreq(midi);
    Oscillator osc;
    osc.setSampleRate(44100);
    osc.setFrequency(freq);

    QVector<float> buffer;
    for (int i = 0; i < durationSec * 44100; ++i)
        buffer.append(osc.sine() * envelope(i, durationSec * 44100));

    processor->playAudio(buffer, 44100);
}
