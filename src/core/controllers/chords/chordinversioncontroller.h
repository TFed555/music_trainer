#ifndef CHORDINVERSIONCONTROLLER_H
#define CHORDINVERSIONCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

class ChordInversionController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    explicit ChordInversionController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
    GeneratedChord result;
};

#endif // CHORDINVERSIONCONTROLLER_H
