#ifndef CHORDIDENTIFYCONTROLLER_H
#define CHORDIDENTIFYCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

class ChordIdentifyController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    explicit ChordIdentifyController(NotePlayer* player, QObject *parent = nullptr);

public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void playTone() override;
private:
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
};

#endif // CHORDIDENTIFYCONTROLLER_H
