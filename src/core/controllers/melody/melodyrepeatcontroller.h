#ifndef MELODYREPEATCONTROLLER_H
#define MELODYREPEATCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

static inline const QMap<Difficulty, MelodyDifficultyConfig> melodyBuildDifficulty = {
    { Difficulty::Easy, {1, 3, 60, 72, {1, 3, 4, 5, 7, 12}} },
    { Difficulty::Hard, {3, 6, 48, 83, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} },
    };

class MelodyRepeatController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit MelodyRepeatController(NotePlayer* player, QObject* parent = nullptr);
public slots:
    void noteSelected(const QString& noteName) override;
    void setDifficulty(int level) override;
signals:
    void setOctaveCount(int count);
private:
    void generateTask() override;
    void playTask() override;
private:
    MelodyDifficultyConfig config = melodyBuildDifficulty[Difficulty::Easy];
    GeneratedAudio result;
    int answerSize = config.noteCount;
};

#endif // MELODYREPEATCONTROLLER_H
