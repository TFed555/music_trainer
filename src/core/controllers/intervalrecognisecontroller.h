#ifndef INTERVALRECOGNISECONTROLLER_H
#define INTERVALRECOGNISECONTROLLER_H

#include "iexercisecontroller.h"
#include "../common/models/Mode.h"

class IntervalRecogniseController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalRecogniseController(NotePlayer* player);

public slots:
    void start() override;
    void stop() override;
    void noteSelected(const QString& name);
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer);

private:
    void playTone();
private:
    QVector<QString> correctAnswer;
    QVector<QString>  userAnswer;
    int noteCounter;
    NotePlayer* notePlayer;
};

#endif // INTERVALRECOGNISECONTROLLER_H
