#ifndef RHYTHMRECOGNISECONTROLLER_H
#define RHYTHMRECOGNISECONTROLLER_H

#include "../common/irhythmexercisecontroller.h"

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
    RhythmDifficultyConfig config = {.replayCount = 2,
                                     .tact = 8.0f,
                                     .allowedDurations = {4},
                                     .bpm = 80};
    float treshold = 10;
    int bpm = 80;
    GeneratedRhythm lastBeats;
    GeneratedRhythm result;
    PlaybackState state = PlaybackState::Idle;
    QString getDescription() const override {
        return tr("Прослушайте ритм и затем простучите его с помощью\n клавиши пробел");
    }
};

#endif // RHYTHMRECOGNISECONTROLLER_H
