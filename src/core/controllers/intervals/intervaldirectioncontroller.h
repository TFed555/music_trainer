#ifndef INTERVALDIRECTIONCONTROLLER_H
#define INTERVALDIRECTIONCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"
#include "../../generators/GeneratedAudio.h"

class IntervalDirectionController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    IntervalDirectionController(NotePlayer* player, QObject* parent = nullptr);

    const QMap<IntervalDirection, QString> directionMap = {
        {IntervalDirection::Ascending, "Ascending"},
        {IntervalDirection::Descending, "Descening"}
    };
public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void playTone() override;
private:
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
};

#endif // INTERVALDIRECTIONCONTROLLER_H
