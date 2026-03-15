#ifndef INTERVALDIRECTIONCONTROLLER_H
#define INTERVALDIRECTIONCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../../generators/GeneratedAudio.h"

class IntervalDirectionController : public IExerciseController
{
    Q_OBJECT
public:
    IntervalDirectionController(NotePlayer* player, QObject* parent = nullptr);
public slots:
    void answerSelected(const QString& answer);
    void setDifficulty(int level) override;
signals:
    void showResult(const QString& correct);
private:
    void playTone() override;
private:
    IntervalDirection correctDirection;
    QString userAnswer;
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
};

#endif // INTERVALDIRECTIONCONTROLLER_H
