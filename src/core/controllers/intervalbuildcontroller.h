#ifndef INTERVALBUILDCONTROLLER_H
#define INTERVALBUILDCONTROLLER_H

#include "iexercisecontroller.h"
#include "../common/models/Mode.h"

class IntervalBuildController : public IExerciseController
{
    Q_OBJECT
public:
    explicit IntervalBuildController(NotePlayer* player, QObject *parent = nullptr);

public slots:
    void noteSelected(const QString& name);
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void setQuestion(const QString& question);
    void highlightQuestion(QVector<QString> notes);
private:
    void playTone() override;
    void onNotesPlayed(const GeneratedAudio& result) override;
private:
    QVector<QString> correctAnswer;
    QVector<QString> userAnswer;
};

#endif // INTERVALBUILDCONTROLLER_H
