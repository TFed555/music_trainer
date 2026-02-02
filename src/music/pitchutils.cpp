#include "pitchutils.h"
#include <cmath>

namespace MusicTheory {
    int freqToMidi(double freq) {
        return static_cast<int>(std::round(12 * std::log2(freq/440) + 69));
    }

    QString midiToNote(int midi) {
        static const char* noteNames[] = { "A", "A#", "B", "C", "C#", "D", "D#",
                                          "E", "E#", "F", "F#", "G", "G#"};
        int noteNum = midi % 12;
        int octaveNum = midi / 12 - 1;

        return QString("%1 %2").arg(noteNames[noteNum]).arg(octaveNum);
    }
}
