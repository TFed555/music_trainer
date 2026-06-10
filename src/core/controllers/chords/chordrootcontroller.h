#ifndef CHORDROOTCONTROLLER_H
#define CHORDROOTCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

class ChordRootController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit ChordRootController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& noteName, const bool listenOnly) override;
    void setDifficulty(int level) override;
    void onOctaveCountChanged(int firstOctave, int lastOctave) override {
        config.octaveCount = lastOctave;
        config.midiMax = 48+lastOctave*12+11;
        config.midiMin = 48+firstOctave*12;
    };
private:
    void generateTask() override;
    void playTask() override;
private:
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
    GeneratedChord result;
    QString getDescription() const override {
        return tr("Определите основную ноту аккорда");
    }
};

#endif // CHORDROOTCONTROLLER_H
