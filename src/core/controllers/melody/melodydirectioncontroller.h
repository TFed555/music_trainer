#ifndef MELODYDIRECTIONCONTROLLER_H
#define MELODYDIRECTIONCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

class MelodyDirectionController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    explicit MelodyDirectionController(NotePlayer* player, QObject* parent = nullptr);
public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    MelodyDifficultyConfig config = difficultyMap<MelodyDifficultyConfig>[Difficulty::Easy];
    GeneratedAudio result;
    QString getDescription() const override {
        return tr("Выберите направление мелодии");
    }
    QVector<QString> getAnswerVariants() const override {
        return MusicUtils::toNameVector(config.directions, MusicUtils::melodyDirectionName);
    }
};

#endif // MELODYDIRECTIONCONTROLLER_H
