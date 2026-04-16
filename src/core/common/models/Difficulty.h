#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QVector>
#include "../../../music/musicutils.h"

enum class Difficulty {
    Easy,
    Hard
};

struct NoteDifficultyConfig {
    int octaveCount = 3;
    int noteCount = 1;
    int midiMin = 48;
    int midiMax = 83;
};


struct IntervalDifficultyConfig {
    QVector<int> allowedSemitones = []{
        QVector<int> v(12);
        std::iota(v.begin(), v.end(), 1);
        return v;
    }();
    int midiMin = 48;
    int midiMax = 83;
    static IntervalDifficultyConfig easy() {
        return {{1, 3, 4, 5, 7, 12}, 60, 72};
    }
    static IntervalDifficultyConfig hard() {
        return {};
    }
};

struct ChordDifficultyConfig {
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
        return {};
    }
    static ChordDifficultyConfig hard() {
        return { 48, 83,
            {MusicUtils::Chords::ChordType::Major, MusicUtils::Chords::ChordType::Minor},
            {MusicUtils::Chords::InversionType::Root,
             MusicUtils::Chords::InversionType::First,
             MusicUtils::Chords::InversionType::Second}
        };
    }
};

struct RhythmDifficultyConfig {
    float tact = 8.0f;
    QVector<int> allowedDurations = {1, 2, 4, 8, 16};
    int bpm = 80;
};

struct MelodyDifficultyConfig : NoteDifficultyConfig {
    QVector<int> allowedSemitones = []{
        QVector<int> v(12);
        std::iota(v.begin(), v.end(), 1);
        return v;
    }();
    QVector<MusicUtils::MelodyDirection> directions;
    static MelodyDifficultyConfig easy() {
        return {1, 3, 60, 72, {1, 3, 4, 5, 7, 12}, {MusicUtils::MelodyDirection::Up, MusicUtils::MelodyDirection::Down}};
    }
    static MelodyDifficultyConfig hard() {
        return {3, 6, 48, 83, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
                {MusicUtils::MelodyDirection::Up, MusicUtils::MelodyDirection::Down, MusicUtils::MelodyDirection::Wavy}};
    }
};

#endif // DIFFICULTY_H
