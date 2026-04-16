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
    void setAnswerVariants();
private:
    MelodyDifficultyConfig config = difficultyMap<MelodyDifficultyConfig>[Difficulty::Easy];
    GeneratedAudio result;
};

#endif // MELODYDIRECTIONCONTROLLER_H
