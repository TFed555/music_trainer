#ifndef INTERVALDIRECTIONCONTROLLER_H
#define INTERVALDIRECTIONCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

class IntervalDirectionController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    IntervalDirectionController(NotePlayer* player, QObject* parent = nullptr);
public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
    GeneratedInterval result;
    QString getDescription() const override {
        return tr("Укажите направление интервала");
    }
    QVector<QString> getAnswerVariants() const override {
        return MusicUtils::toNameVector(config.allowedDirection, MusicUtils::Intervals::intervalDirectionName);
    }
};

#endif // INTERVALDIRECTIONCONTROLLER_H
