#ifndef NOTEGUESSCONTROLLER_H
#define NOTEGUESSCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteGuessDifficulty = {
    { Difficulty::Easy, { .replayCount = 2,
                           .octaveCount = 3,
                           .noteCount = 3,
                           .midiMin = 60,
                           .midiMax = 72
                       }},
    { Difficulty::Hard, { .replayCount = 1,
                           .octaveCount = 3,
                           .noteCount = 5,
                           .midiMin = 48,
                           .midiMax = 83
                       }},
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
    QString getDescription() const override {
        return tr("Определите одинаковые или разные \nпервая и последняя ноты в мелодии");
    }
    QVector<QString> getAnswerVariants() const override {
        return MusicUtils::noteGuessName();
    }
};

#endif // NOTEGUESSCONTROLLER_H
