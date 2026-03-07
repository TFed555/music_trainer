#ifndef PITCHUTILS_H
#define PITCHUTILS_H

#include <QString>
#include <QList>
#include <QMap>

namespace MusicUtils {

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

QString semitonesToInterval(int semitones);

enum class ChordType {
    Major,
    Minor
};

inline const QMap<ChordType, QString> chordTypeNames = {
    { ChordType::Major, "мажор" },
    { ChordType::Minor, "минор" }
};

}

#endif // PITCHUTILS_H
