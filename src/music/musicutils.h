#ifndef MUSICUTILS_H
#define MUSICUTILS_H

#include <QString>
#include <QList>
#include <QMap>
#include <QCoreApplication>

namespace MusicUtils {

template <typename T, typename NameFunc>
QVector<QString> toNameVector(const QVector<T>& keys, NameFunc func) {
    QVector<QString> result;
    result.reserve(keys.size());
    for (const auto& key : keys) {
        auto val = func(key);
        if (val != "") {
            result.append(val);
        }
    }
    return result;
}

QString midiToNote(int midi);

int noteToMidi(QString note);

static const char* noteNames[] = { "C", "C#", "D", "D#", "E",
                                  "F", "F#", "G", "G#", "A", "A#", "B" };

enum class MelodyDirection {
    Up,
    Down,
    Wavy
};

static const QMap<MelodyDirection, QString> melodyDirNames = {
    { MelodyDirection::Up, "восходящее" },
    { MelodyDirection::Down, "нисходящее" },
    { MelodyDirection::Wavy, "волнообразное"},
    };

inline QString melodyDirectionName(MelodyDirection dir) {
    static const QMap<MelodyDirection, const char*> names = {
                                                              {MelodyDirection::Up,   QT_TRANSLATE_NOOP("Melody", "восходящее")},
                                                              {MelodyDirection::Down, QT_TRANSLATE_NOOP("Melody", "нисходящее")},
                                                              {MelodyDirection::Wavy, QT_TRANSLATE_NOOP("Melody", "волнообразное")},
                                                              };
    return QCoreApplication::translate("Melody", names.value(dir, ""));
}

inline QVector<QString> noteGuessName() {
    static const char* same    = QT_TRANSLATE_NOOP("Notes", "одинаковые");
    static const char* diff    = QT_TRANSLATE_NOOP("Notes", "разные");
    return {
        QCoreApplication::translate("Notes", same),
        QCoreApplication::translate("Notes", diff)
    };
}
    namespace Intervals {
    inline QString intervalName(int semitones) {
        static const QMap<int, const char*> names = {
                                                      {0,  QT_TRANSLATE_NOOP("Intervals", "прима")},
                                                      {1,  QT_TRANSLATE_NOOP("Intervals", "малая секунда")},
                                                      {2,  QT_TRANSLATE_NOOP("Intervals", "большая секунда")},
                                                      {3,  QT_TRANSLATE_NOOP("Intervals", "малая терция")},
                                                      {4,  QT_TRANSLATE_NOOP("Intervals", "большая терция")},
                                                      {5,  QT_TRANSLATE_NOOP("Intervals", "кварта")},
                                                      {6,  QT_TRANSLATE_NOOP("Intervals", "тритон")},
                                                      {7,  QT_TRANSLATE_NOOP("Intervals", "квинта")},
                                                      {8,  QT_TRANSLATE_NOOP("Intervals", "малая секста")},
                                                      {9,  QT_TRANSLATE_NOOP("Intervals", "большая секста")},
                                                      {10, QT_TRANSLATE_NOOP("Intervals", "малая септима")},
                                                      {11, QT_TRANSLATE_NOOP("Intervals", "большая септима")},
                                                      {12, QT_TRANSLATE_NOOP("Intervals", "октава")},
                                                      };
        return QCoreApplication::translate("Intervals", names.value(semitones, ""));
    }

    inline QList<QString> intervalNames() {
        return {
            intervalName(0), intervalName(1), intervalName(2),
            intervalName(3), intervalName(4), intervalName(5),
            intervalName(6), intervalName(7), intervalName(8),
            intervalName(9), intervalName(10), intervalName(11), intervalName(12)
        };
    }

    inline const QList<QString> intervals =
        {
            "прима", "малая секунда", "большая секунда", "малая терция", "большая терция",
            "кварта", "тритон", "квинта", "малая секста", "большая секста", "малая септима",
            "большая септима", "октава"
        };

    QString semitonesToInterval(int semitones);

    enum class IntervalDirection {
        Ascending,
        Descending
    };

    inline QString intervalDirectionName(IntervalDirection dir) {
        static const QMap<IntervalDirection, const char*> names = {
                                                                {IntervalDirection::Ascending,  QT_TRANSLATE_NOOP("Intervals", "возрастающий")},
                                                                {IntervalDirection::Descending,  QT_TRANSLATE_NOOP("Intervals", "убывающий")},
                                                                };
        return QCoreApplication::translate("Intervals", names.value(dir, ""));
    }

    }

    namespace Chords {
    enum class ChordType {
        Major,
        Minor,
        DiminishedTriad,
        AugmentedTriad,
        MajorSeventhChord,
        MinorSeventhChord
    };

    enum class InversionType {
        Root,
        First,
        Second
    };

    inline QString chordName(ChordType type) {
        static const QMap<ChordType, const char*> names = {
                                                      {ChordType::Major,  QT_TRANSLATE_NOOP("Chords", "мажор")},
                                                      {ChordType::Minor,  QT_TRANSLATE_NOOP("Chords", "минор")},
                                                      {ChordType::AugmentedTriad,  QT_TRANSLATE_NOOP("Chords", "увеличенное трезвучие")},
                                                      {ChordType::DiminishedTriad,  QT_TRANSLATE_NOOP("Chords", "уменьшенное трезвучие")},
                                                      {ChordType::MajorSeventhChord,  QT_TRANSLATE_NOOP("Chords", "малый мажорный септаккорд")},
                                                      {ChordType::MinorSeventhChord,  QT_TRANSLATE_NOOP("Chords", "малый минорный септаккорд")},
                                                      };
        return QCoreApplication::translate("Chords", names.value(type, ""));
    }

    inline QString inversionName(InversionType type) {
        static const QMap<InversionType, const char*> names = {
                                                            {InversionType::Root,  QT_TRANSLATE_NOOP("Chords", "Исходная")},
                                                            {InversionType::First,  QT_TRANSLATE_NOOP("Chords", "1-я инверсия")},
                                                            {InversionType::Second,  QT_TRANSLATE_NOOP("Chords", "2-я инверсия")},
                                                            };
        return QCoreApplication::translate("Chords", names.value(type, ""));
    }

    inline const QMap<ChordType, QString> chordTypeNames = {
        { ChordType::Major, "мажор" },
        { ChordType::Minor, "минор" },
        { ChordType::AugmentedTriad, "увеличенное трезвучие"},
        { ChordType::DiminishedTriad, "уменьшенное трезвучие"},
        { ChordType::MajorSeventhChord, "малый мажорный септаккорд"},
        { ChordType::MinorSeventhChord, "малый минорный септаккорд"},
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
        Ordinary,
        UserBeat
    };
    enum class RhythmType
    {
        Whole,
        Half,
        Quarter,
        Eighth,
        Sixteenth
    };
    inline const QVector<RhythmType> allDurations = {
        RhythmType::Whole,
        RhythmType::Half,
        RhythmType::Quarter,
        RhythmType::Eighth,
        RhythmType::Sixteenth
    };

    inline QString durationName(RhythmType type) {
        static const QMap<RhythmType, const char*> names = {
            {RhythmType::Whole,  QT_TRANSLATE_NOOP("Rhythm", "Целая")},
            {RhythmType::Half,  QT_TRANSLATE_NOOP("Rhythm", "Половинная")},
            {RhythmType::Quarter,  QT_TRANSLATE_NOOP("Rhythm", "Четвертная")},
            {RhythmType::Eighth,  QT_TRANSLATE_NOOP("Rhythm", "Восьмая")},
            {RhythmType::Sixteenth,  QT_TRANSLATE_NOOP("Rhythm", "Шестнадцатая")},
                                                            };
        return QCoreApplication::translate("Rhythm", names.value(type, ""));
    }


    inline const QMap<int, RhythmType> rhythmTypeNames = {
        {1, RhythmType::Whole},
        {2, RhythmType::Half},
        {4, RhythmType::Quarter},
        {8, RhythmType::Eighth},
        {16, RhythmType::Sixteenth}
    };

    }

}

#endif // MUSICUTILS_H
