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
    void playTone() override;
private:
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
};

#endif // INTERVALBUILDCONTROLLER_H
