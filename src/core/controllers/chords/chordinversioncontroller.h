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
    void playTone() override;
private:
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
};

#endif // CHORDINVERSIONCONTROLLER_H
