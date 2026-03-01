#ifndef INTERVALIDENTIFYCONTROLLER_H
#define INTERVALIDENTIFYCONTROLLER_H

#include <QObject>
#include "iexercisecontroller.h"
#include "../../music/pitchutils.h"

class IntervalIdentifyController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalIdentifyController(NotePlayer* player);
public slots:
    void start() override;
    void stop() override;
    void answerSelected(const QString& answer);
signals:
    void setAnswers(QVector<QString> answers);
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
