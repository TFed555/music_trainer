#ifndef NOTEPLAYER_H
#define NOTEPLAYER_H
#pragma once

#include "../audio.h"

class NotePlayer {
public:
    explicit NotePlayer(AudioProcessor* processor = nullptr);

    void playMidi(int midi, float durationSec = 0.5f);
private:
    AudioProcessor* processor;
};

#endif // NOTEPLAYER_H
