#ifndef MELODYREPEATCONTROLLER_H
#define MELODYREPEATCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

class MelodyRepeatController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit MelodyRepeatController(NotePlayer* player, QObject* parent = nullptr);
public slots:
    void noteSelected(const QString& noteName, const bool listenOnly) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    MelodyDifficultyConfig config = difficultyMap<MelodyDifficultyConfig>[Difficulty::Easy];
    GeneratedAudio result;
    int answerSize = config.noteCount;
    QString getDescription() const override {
        return tr("Повторите мелодию");
    }
};

#endif // MELODYREPEATCONTROLLER_H
