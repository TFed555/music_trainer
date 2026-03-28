#ifndef INTERVALIDENTIFYCONTROLLER_H
#define INTERVALIDENTIFYCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

class IntervalIdentifyController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    explicit IntervalIdentifyController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void playTone() override;
private:
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
};

#endif // INTERVALIDENTIFYCONTROLLER_H
