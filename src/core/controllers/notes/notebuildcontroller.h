#ifndef NOTEBUILDCONTROLLER_H
#define NOTEBUILDCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteBuildDifficulty = {
    { Difficulty::Easy, {1, 1, 60, 72} },
    { Difficulty::Hard, {} },
    };

class NoteBuildController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit NoteBuildController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& noteName) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    NoteDifficultyConfig config = noteBuildDifficulty[Difficulty::Easy];
    GeneratedAudio result;
};

#endif // NOTEBUILDCONTROLLER_H
