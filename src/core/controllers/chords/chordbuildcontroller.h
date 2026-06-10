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
    void onOctaveCountChanged(int firstOctave, int lastOctave) override {
        config.octaveCount = lastOctave;
        config.midiMax = 48+lastOctave*12+11;
        config.midiMin = 48+firstOctave*12;
    };
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
