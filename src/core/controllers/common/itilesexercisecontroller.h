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
    virtual void noteSelected(const QString& noteName, const bool listenOnly) = 0;
    void retranslate() {
        sendDescription();
    };
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void highlightQuestion(QVector<QString> notes);
    void setQuestion(const QString& question);
    void setOctaveCount(int count);
protected:
    QVector<QString> correctAnswer;
    QVector<QString> userAnswer;
    static constexpr int firstNoteIdx = 0;
    static constexpr int secondNoteIdx = 1;

QString vecToStr(const QVector<QString>& v) {
        return v.join(", ");
}
};

#endif // ITILESEXERCISECONTROLLER_H
