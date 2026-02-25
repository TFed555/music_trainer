#ifndef NOTEPLAYER_H
#define NOTEPLAYER_H
#pragma once

#include "../audio.h"
#include "../core/data/samples/samplerepository.h"
#include <samplerate.h>

class NotePlayer {
public:
    explicit NotePlayer(AudioProcessor* processor = nullptr, SampleRepository* sampleRepo = nullptr);

    void playMidi(int midi, float durationSec = 0.5f);
private:
    AudioProcessor* processor;
    SampleRepository* sampleRepository;
};

#endif // NOTEPLAYER_H
