#ifndef CHORDBUILDCONTROLLER_H
#define CHORDBUILDCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

class ChordBuildController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit ChordBuildController(NotePlayer* player,
                                  QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& noteName, const bool listenOnly) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    int noteCounter = 0;
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
    static constexpr int chordNoteCount = 2;
    static constexpr int thirdNoteIdx = 2;
    GeneratedChord result;
    QString getDescription() const override {
        return tr("Постройте аккорд нужной тональности");
    }
};

#endif // CHORDBUILDCONTROLLER_H
