#include "pitchutils.h"
#include <cmath>

namespace MusicTheory {
    int freqToMidi(double freq) {
        return static_cast<int>(std::round(12 * std::log2(freq/440) + 69));
    }

    QString midiToNote(int midi) {
        int noteNum = midi % 12;
        int octaveNum = midi / 12 - 1;
        return QString("%1").arg(noteNames[noteNum]);
        // return QString("%1 %2").arg(noteNames[noteNum]).arg(octaveNum);
    }

    int noteToMidi(QString note) {
        int noteIndex;
        for (size_t i = 0; i < 12; i++) {
            if (note == noteNames[i]) {
                noteIndex = i; break;
            }
        }

        return 5 * 12 + noteIndex;
    }

    double midiToFreq(int midi) {
        return std::pow(2.0, (midi-69)/12.0)*440.0;
    }
}
