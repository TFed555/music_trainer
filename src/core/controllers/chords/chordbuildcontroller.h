#ifndef CHORDBUILDCONTROLLER_H
#define CHORDBUILDCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../common/models/Mode.h"

class ChordBuildController : public IExerciseController
{
    Q_OBJECT
public:
    explicit ChordBuildController(NotePlayer* player,
                                  QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& name);
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void setQuestion(const QString& question);
    void highlightQuestion(QVector<QString> notes);
private:
    void playTone() override;
private:
    QVector<QString> correctAnswer;
    QVector<QString> userAnswer;
    int noteCounter = 0;
};

#endif // CHORDBUILDCONTROLLER_H
