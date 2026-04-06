#ifndef ITILESEXERCISECONTROLLER_H
#define ITILESEXERCISECONTROLLER_H

#include "iexercisecontroller.h"
#include "../../common/models/Mode.h"

class ITilesExerciseController : public IExerciseController
{
    Q_OBJECT
public:
    using IExerciseController::IExerciseController;
public slots:
    virtual void noteSelected(const QString& noteName) = 0;
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void highlightQuestion(QVector<QString> notes);
    void setQuestion(const QString& question);
protected:
    QVector<QString> correctAnswer;
    QVector<QString> userAnswer;
    static constexpr int firstNoteIdx = 0;
    static constexpr int secondNoteIdx = 1;
};

#endif // ITILESEXERCISECONTROLLER_H
