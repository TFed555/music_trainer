#ifndef NOTEBUILDCONTROLLER_H
#define NOTEBUILDCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../common/models/Mode.h"

class NoteBuildController : public IExerciseController
{
    Q_OBJECT
public:
    explicit NoteBuildController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& name);
    void setDifficulty(int level) override;
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void setQuestion(const QString& question);
    void highlightQuestion(QVector<QString> notes);
    void setOctaveCount(int count);
private:
    void playTone() override;
private:
    QVector<QString> correctAnswer;
    QVector<QString> userAnswer;
    NoteDifficultyConfig config = difficultyMap<NoteDifficultyConfig>[Difficulty::Easy];
};

#endif // NOTEBUILDCONTROLLER_H
