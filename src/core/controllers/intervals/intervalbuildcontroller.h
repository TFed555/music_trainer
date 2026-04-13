#ifndef INTERVALBUILDCONTROLLER_H
#define INTERVALBUILDCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

class IntervalBuildController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit IntervalBuildController(NotePlayer* player,
                                    QObject *parent = nullptr);

public slots:
    void noteSelected(const QString& noteName) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
    GeneratedInterval result;
};

#endif // INTERVALBUILDCONTROLLER_H
