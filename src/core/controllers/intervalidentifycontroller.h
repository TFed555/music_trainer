#ifndef INTERVALIDENTIFYCONTROLLER_H
#define INTERVALIDENTIFYCONTROLLER_H

#include "iexercisecontroller.h"
#include "../../music/pitchutils.h"

class IntervalIdentifyController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalIdentifyController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void answerSelected(const QString& answer);
    void giveAnswers();
signals:
    void setAnswers(QVector<QString>);
    void showResult(const QString& correct);
private:
    void playTone() override;
    void onNotesPlayed(const GeneratedAudio& result) override;
private:
    QVector<QString> answerVariants = MusicUtils::intervals;
    QString correctAnswer;
    QString userAnswer;
};

#endif // INTERVALIDENTIFYCONTROLLER_H
