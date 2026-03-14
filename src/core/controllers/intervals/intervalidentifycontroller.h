#ifndef INTERVALIDENTIFYCONTROLLER_H
#define INTERVALIDENTIFYCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../music/pitchutils.h"

class IntervalIdentifyController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalIdentifyController(NotePlayer* player, QObject *parent = nullptr);
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
    QVector<QString> answerVariants = MusicUtils::Intervals::intervals;
    QString correctAnswer;
    QString userAnswer;
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
};

#endif // INTERVALIDENTIFYCONTROLLER_H
