#ifndef NOTERECOGNISECONTROLLER_H
#define NOTERECOGNISECONTROLLER_H

#include "../common/itilesexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteRecogniseDifficulty = {
    { Difficulty::Easy, { .replayCount = 2,
                           .octaveCount = 1,
                           .noteCount = 1,
                           .midiMin = 60,
                           .midiMax = 72
                        }},
    { Difficulty::Hard, {} },
    };

class NoteRecogniseController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit NoteRecogniseController(NotePlayer* player, QObject *parent = nullptr);
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
    NoteDifficultyConfig config = noteRecogniseDifficulty[Difficulty::Easy];
    GeneratedAudio result;
    QString getDescription() const override {
        return tr("Укажите услышанную ноту \nна клавиатуре");
    }
};

#endif // NOTERECOGNISECONTROLLER_H
