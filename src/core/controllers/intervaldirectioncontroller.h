#ifndef INTERVALDIRECTIONCONTROLLER_H
#define INTERVALDIRECTIONCONTROLLER_H

#include "iexercisecontroller.h"

class IntervalDirectionController : public IExerciseController
{
    Q_OBJECT
public:
    IntervalDirectionController(NotePlayer* player, QObject* parent = nullptr);
public slots:
    void answerSelected(const QString& answer);
signals:
    void setAnswers(QVector<QString>);
    void showResult(const QString& correct);
private:
    void playTone() override;
    void onNotesPlayed(const GeneratedAudio& result) override;
private:
    IntervalDirection correctDirection;
    QString userAnswer;
};

#endif // INTERVALDIRECTIONCONTROLLER_H
