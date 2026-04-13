#ifndef NOTEGUESSCONTROLLER_H
#define NOTEGUESSCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteGuessDifficulty = {
    { Difficulty::Easy, {3, 3, 60, 72} },
    { Difficulty::Hard, {3, 5, 48, 83} },
};

class NoteGuessController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    explicit NoteGuessController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    NoteDifficultyConfig config = noteGuessDifficulty[Difficulty::Easy];
    GeneratedAudio result;
};

#endif // NOTEGUESSCONTROLLER_H
