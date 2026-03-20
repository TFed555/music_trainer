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

    namespace Intervals {
    inline const QList<QString> intervals =
        {
            "прима", "малая секунда", "большая секунда", "малая терция", "большая терция",
            "кварта", "тритон", "квинта", "малая секста", "большая секста", "малая септима",
            "большая септима", "октава"
        };

    QString semitonesToInterval(int semitones);
    }

    namespace Chords {
    enum class ChordType {
        Major,
        Minor
    };

    enum class InversionType {
        Root,
        First,
        Second
    };

    inline const QMap<ChordType, QString> chordTypeNames = {
        { ChordType::Major, "мажор" },
        { ChordType::Minor, "минор" }
    };

    inline const QMap<InversionType, QString> inversionNames = {
        { InversionType::Root,   "Исходная" },
        { InversionType::First,  "1-я инверсия" },
        { InversionType::Second, "2-я инверсия" }
    };
    }

    namespace Rhythm {
    enum class BeatType {
        Accent,
        Ordinary
    };
    enum class RhythmType
    {
        Whole,
        Half,
        Quarter,
        Eighth,
        Sixteenth
    };

    inline const QMap<int, RhythmType> rhythmTypeNames = {
        {1, RhythmType::Whole},
        {2, RhythmType::Half},
        {4, RhythmType::Quarter},
        {8, RhythmType::Eighth},
        {16, RhythmType::Sixteenth}
    };

    }

}

#endif // PITCHUTILS_H
