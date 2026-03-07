#ifndef PITCHUTILS_H
#define PITCHUTILS_H

#include <QString>
#include <QList>

namespace MusicUtils {

int freqToMidi(double freq);

double midiToFreq(int midi);

QString midiToNote(int midi);

int noteToMidi(QString note);

static const char* noteNames[] = { "C", "C#", "D", "D#", "E",
                                  "F", "F#", "G", "G#", "A", "A#", "B" };

inline const QList<QString> intervals =
    {
        "прима", "малая секунда", "большая секунда", "малая терция", "большая терция",
        "кварта", "тритон", "квинта", "малая секста", "большая секста", "малая септима",
        "большая септима", "октава"
    };

inline const QList<QString>  chordTones = {
    "мажор", "минор"
    };

QString semitonesToInterval(int semitones);
}

#endif // PITCHUTILS_H
