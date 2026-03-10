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
signals:
    void setAnswers(QVector<QString>);
    void showResult(const QString& correct);
private:
    void playTone() override;
private:
    IntervalDirection correctDirection;
    QString userAnswer;
};

#endif // INTERVALDIRECTIONCONTROLLER_H
