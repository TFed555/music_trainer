#ifndef PITCHUTILS_H
#define PITCHUTILS_H

#include <QString>

namespace MusicTheory {

int freqToMidi(double freq);

double midiToFreq(int midi);

QString midiToNote(int midi);

int noteToMidi(QString note);

static const char* noteNames[] = { "A", "A#", "B", "C", "C#", "D", "D#",
                                  "E", "E#", "F", "F#", "G", "G#"};

}

#endif // PITCHUTILS_H
