#ifndef INTERVALRECOGNISECONTROLLER_H
#define INTERVALRECOGNISECONTROLLER_H

#include "../common/itilesexercisecontroller.h"
#include "../../common/models/Note.h"

class IntervalRecogniseController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit IntervalRecogniseController(NotePlayer* player, QObject *parent = nullptr);

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
    int noteCounter;
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
    static constexpr int intervalNoteCount = 2;
    GeneratedInterval result;
    QString getDescription() const override {
        return tr("Укажите интервал на клавиатуре");
    }
};

#endif // INTERVALRECOGNISECONTROLLER_H
