#ifndef NOTERECOGNISECONTROLLER_H
#define NOTERECOGNISECONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../common/models/Mode.h"

class NoteRecogniseController : public IExerciseController
{
    Q_OBJECT
public:
    explicit NoteRecogniseController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& name);
    void setDifficulty(int level) override;
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
private:
    void playTone() override;
private:
    QVector<QString> correctAnswer;
    QVector<QString>  userAnswer;
    int noteCounter;
    NoteDifficultyConfig config = difficultyMap<NoteDifficultyConfig>[Difficulty::Easy];
};

#endif // NOTERECOGNISECONTROLLER_H
