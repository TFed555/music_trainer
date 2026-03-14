#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QVector>
#include "../../../music/pitchutils.h"

enum class Difficulty {
    Easy,
    Hard
};

struct NoteDifficultyConfig {
    int midiMin = 48;
    int midiMax = 83;
    static NoteDifficultyConfig easy() {
        return {60, 72};
    }
    static NoteDifficultyConfig hard() {
        return {};
    }
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
        return {
            {MusicUtils::Chords::ChordType::Major, MusicUtils::Chords::ChordType::Minor},
            {MusicUtils::Chords::InversionType::Root,
             MusicUtils::Chords::InversionType::First,
             MusicUtils::Chords::InversionType::Second}
        };
    }
};


#endif // DIFFICULTY_H
