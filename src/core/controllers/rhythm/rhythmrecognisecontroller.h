#ifndef RHYTHMRECOGNISECONTROLLER_H
#define RHYTHMRECOGNISECONTROLLER_H

#include "../common/iexercisecontroller.h"

class RhythmRecogniseController : public IExerciseController
{
    Q_OBJECT
public:
    explicit RhythmRecogniseController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void setDifficulty(int level) override;
private:
    void playTone() override;
private:
    RhythmDifficultyConfig config = difficultyMap<RhythmDifficultyConfig>[Difficulty::Easy];
};

#endif // RHYTHMRECOGNISECONTROLLER_H
