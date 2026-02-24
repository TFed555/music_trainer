#include "noteplayer.h"
#include <QDebug>
#include "../../music/pitchutils.h"

NotePlayer::NotePlayer(AudioProcessor* proc, SampleRepository* sampleRepo)
    : processor(proc), sampleRepository{sampleRepo}
{}

void NotePlayer::playMidi(int midi, float durationSec) {
    Sample buffer = sampleRepository->getSample(44);
    processor->playAudio(buffer.data, buffer.sampleRate);
}
