#ifndef RHYTHMRECOGNISECONTROLLER_H
#define RHYTHMRECOGNISECONTROLLER_H

#include "../common/irhythmexercisecontroller.h"

// static inline const QMap<Difficulty, RhythmDifficultyConfig> rhythmRecogniseDifficulty = {
//     { Difficulty::Easy, {8.0, {4}, 80}},
//     { Difficulty::Hard, {8.0, {2, 4}, 120}},
// };

class RhythmRecogniseController : public IRhythmExerciseController
{
    Q_OBJECT
public:
    explicit RhythmRecogniseController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void setDifficulty(int level) override;
    void inputFinished(const QVector<int>& notePoses, const QVector<int>& userTaps) override;
    void setConfig(const QMap<int,int>& states) override;
    void bpmChanged(const int& bpm) override;
    void onBeatFinished();
private:
    void generateTask() override;
    void playTask() override;
    enum class PlaybackState { Idle, Metronome, Task };
private:
    RhythmDifficultyConfig config = {8.0f, {4}, 80};
    float treshold = 10;
    int bpm = 80;
    GeneratedRhythm lastBeats;
    GeneratedRhythm result;
    PlaybackState state = PlaybackState::Idle;
};

#endif // RHYTHMRECOGNISECONTROLLER_H
