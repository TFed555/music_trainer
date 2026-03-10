#include "pitchutils.h"
#include <cmath>
#include <QDebug>

namespace MusicUtils {

    QString midiToNote(int midi) {
        int noteNum = midi % 12;
        int octaveNum = midi / 12 - 1;
        // return QString("%1").arg(noteNames[noteNum]);
        return QString("%1 %2").arg(noteNames[noteNum]).arg(octaveNum);
    }

    int noteToMidi(QString note) {
        auto list = note.split(" ");
        int octaveNum = list[1].toInt();
        int noteIndex;
        for (int i = 0; i < 12; i++) {
            if (list[0] == noteNames[i]) {
                noteIndex = i; break;
            }
        }

        return (octaveNum + 1) * 12 + noteIndex;
    }

    namespace Intervals{
    QString semitonesToInterval(int semitones) {
        qDebug() << semitones;
        qDebug() << intervals.value(semitones);
        return static_cast<QString>(intervals.value(semitones));
    }
    }
}
