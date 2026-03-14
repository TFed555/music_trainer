#ifndef INTERVALBUILDCONTROLLER_H
#define INTERVALBUILDCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../common/models/Mode.h"

class IntervalBuildController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalBuildController(NotePlayer* player,
                                    QObject *parent = nullptr);

public slots:
    void noteSelected(const QString& name);
    void setDifficulty(int level) override;
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void setQuestion(const QString& question);
    void highlightQuestion(QVector<QString> notes);
private:
    void playTone() override;
private:
    QVector<QString> correctAnswer;
    QVector<QString> userAnswer;
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
};

#endif // INTERVALBUILDCONTROLLER_H
