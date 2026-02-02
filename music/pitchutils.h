#ifndef PITCHUTILS_H
#define PITCHUTILS_H

#include <QString>

namespace MusicTheory {

int freqToMidi(double freq);

QString midiToNote(int midi);

}

#endif // PITCHUTILS_H
