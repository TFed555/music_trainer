#ifndef CHORDROOTCONTROLLER_H
#define CHORDROOTCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../common/models/Mode.h"

class ChordRootController : public IExerciseController
{
    Q_OBJECT
public:
    explicit ChordRootController(NotePlayer* player, QObject *parent = nullptr);
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
};

#endif // CHORDROOTCONTROLLER_H
