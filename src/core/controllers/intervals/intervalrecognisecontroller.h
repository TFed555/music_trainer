#ifndef INTERVALRECOGNISECONTROLLER_H
#define INTERVALRECOGNISECONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../common/models/Mode.h"

class IntervalRecogniseController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalRecogniseController(NotePlayer* player, QObject *parent = nullptr);

public slots:
    void noteSelected(const QString& name);
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
private:
    void playTone() override;
private:
    QVector<QString> correctAnswer;
    QVector<QString>  userAnswer;
    int noteCounter;
};

#endif // INTERVALRECOGNISECONTROLLER_H
