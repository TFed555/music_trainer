#ifndef CHORDINVERSIONCONTROLLER_H
#define CHORDINVERSIONCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../music/pitchutils.h"

class ChordInversionController : public IExerciseController
{
    Q_OBJECT
public:
    explicit ChordInversionController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void answerSelected(const QString& answer);
    void giveAnswers();
signals:
    void setAnswers(QVector<QString>);
    void showResult(const QString& correct);
private:
    void playTone() override;
private:
    QVector<QString> answerVariants = MusicUtils::Chords::inversionNames.values();
    QString correctAnswer;
    QString userAnswer;
};

#endif // CHORDINVERSIONCONTROLLER_H
