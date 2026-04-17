#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QVector>
#include "../../../music/musicutils.h"

enum class Difficulty {
    Easy,
    Hard
};

struct NoteDifficultyConfig {
    int replayCount = 1;
    int octaveCount = 3;
    int noteCount = 1;
    int midiMin = 48;
    int midiMax = 83;
};


struct IntervalDifficultyConfig {
    int replayCount = 1;
    QVector<int> allowedSemitones = []{
        QVector<int> v(12);
        std::iota(v.begin(), v.end(), 1);
        return v;
    }();
    int midiMin = 48;
    int midiMax = 83;
    static IntervalDifficultyConfig easy() {
        return { .replayCount = 2,
                .allowedSemitones = {1, 3, 4, 5, 7, 12},
                .midiMin = 60,
                .midiMax = 72
            };
    }
    static IntervalDifficultyConfig hard() {
        return {};
    }
};

struct ChordDifficultyConfig {
    int replayCount = 1;
    int midiMin = 48;
    int midiMax = 83;
    QVector<MusicUtils::Chords::ChordType> allowedTypes = {
        MusicUtils::Chords::ChordType::Major,
        MusicUtils::Chords::ChordType::Minor
    };
    QVector<MusicUtils::Chords::InversionType> allowedInversions = {
        MusicUtils::Chords::InversionType::Root,
    };
    static ChordDifficultyConfig easy() {
        return {.replayCount = 2,
                .midiMin = 48,
                .midiMax = 83,
                .allowedTypes = {MusicUtils::Chords::ChordType::Major, MusicUtils::Chords::ChordType::Minor},
                .allowedInversions = { MusicUtils::Chords::InversionType::Root}
                };
    }
    static ChordDifficultyConfig hard() {
        return {.replayCount = 1,
                .midiMin = 48,
                .midiMax = 83,
                .allowedTypes = {MusicUtils::Chords::ChordType::Major, MusicUtils::Chords::ChordType::Minor},
                .allowedInversions = {MusicUtils::Chords::InversionType::Root,
                                         MusicUtils::Chords::InversionType::First,
                                         MusicUtils::Chords::InversionType::Second}
        };
    }
};

struct RhythmDifficultyConfig {
    int replayCount = 1;
    float tact = 8.0f;
    QVector<int> allowedDurations = {1, 2, 4, 8, 16};
    int bpm = 80;
};

struct MelodyDifficultyConfig : NoteDifficultyConfig {
    int replayCount = 1;
    int octaveCount = 3;
    int noteCount = 1;
    int midiMin = 48;
    int midiMax = 83;
    QVector<int> allowedSemitones = []{
        QVector<int> v(12);
        std::iota(v.begin(), v.end(), 1);
        return v;
    }();
    QVector<MusicUtils::MelodyDirection> directions;
    static MelodyDifficultyConfig easy() {
        return {.replayCount = 2,
                .octaveCount = 1,
                .noteCount = 3,
                .midiMin = 60,
                .midiMax = 72,
                .allowedSemitones = {1, 3, 4, 5, 7, 12},
                .directions = {MusicUtils::MelodyDirection::Up, MusicUtils::MelodyDirection::Down}
        };
    }
    static MelodyDifficultyConfig hard() {
        return {.replayCount = 1,
            .octaveCount = 3,
            .noteCount = 6,
            .midiMin = 48,
            .midiMax = 83,
            .allowedSemitones = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
            .directions = {MusicUtils::MelodyDirection::Up, MusicUtils::MelodyDirection::Down, MusicUtils::MelodyDirection::Wavy}
        };
    }
};

#endif // DIFFICULTY_H
