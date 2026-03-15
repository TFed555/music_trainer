#ifndef NOTEGUESSCONTROLLER_H
#define NOTEGUESSCONTROLLER_H

#include "../common/iexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteGuessDifficulty = {
    { Difficulty::Easy, {3, 3, 60, 72} },
    { Difficulty::Hard, {3, 5, 48, 83} },
};

class NoteGuessController : public IExerciseController
{
    Q_OBJECT
public:
    explicit NoteGuessController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void answerSelected(const QString& answer);
    void giveAnswers();
    void setDifficulty(int level) override;
signals:
    void setAnswers(QVector<QString>);
    void showResult(const QString& correct);
private:
    void playTone() override;
private:
    QVector<QString> answerVariants = {"одинаковые", "разные"};
    QString correctAnswer;
    QString userAnswer;
    NoteDifficultyConfig config = noteGuessDifficulty[Difficulty::Easy];
};

#endif // NOTEGUESSCONTROLLER_H
