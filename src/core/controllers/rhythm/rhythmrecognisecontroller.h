#ifndef RHYTHMRECOGNISECONTROLLER_H
#define RHYTHMRECOGNISECONTROLLER_H

#include "../common/iexercisecontroller.h"

static inline const QMap<Difficulty, RhythmDifficultyConfig> rhythmRecogniseDifficulty = {
    { Difficulty::Easy, {8.0, {4}, 80}},
    { Difficulty::Hard, {8.0, {2, 4}, 120}},
};

class RhythmRecogniseController : public IExerciseController
{
    Q_OBJECT
public:
    explicit RhythmRecogniseController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void setDifficulty(int level) override;
    void inputFinished(const QVector<int>& notePoses, const QVector<int>& userTaps);
signals:
    void setRhythmNotes(const QVector<MusicUtils::Rhythm::RhythmType>&, int bpm);
    void result(const int correct, const int wrong);
private:
    void playTone() override;
private:
    RhythmDifficultyConfig config = rhythmRecogniseDifficulty[Difficulty::Easy];
    float treshold = 10;
};

#endif // RHYTHMRECOGNISECONTROLLER_H
