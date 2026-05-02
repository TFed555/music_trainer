#ifndef ICHOICEEXERCISECONTROLLER_H
#define ICHOICEEXERCISECONTROLLER_H

#include "iexercisecontroller.h"

class IChoiceExerciseController : public IExerciseController
{
    Q_OBJECT
public:
    using IExerciseController::IExerciseController;
public slots:
    virtual void answerSelected(const QString& answer) = 0;
    void giveAnswers() { emit setAnswers(getAnswerVariants()); }
    void retranslate() {
        sendDescription();
        giveAnswers();
    };
signals:
    void showResult(const QString& correct);
    void setAnswers(QVector<QString>);
protected:
    QString correctAnswer;
    QString userAnswer;
    static constexpr int firstNoteIdx = 0;
    static constexpr int secondNoteIdx = 1;
    virtual QVector<QString> getAnswerVariants() const = 0;
};

#endif // ICHOICEEXERCISECONTROLLER_H
