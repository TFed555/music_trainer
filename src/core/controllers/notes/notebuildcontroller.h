#ifndef NOTEBUILDCONTROLLER_H
#define NOTEBUILDCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteBuildDifficulty = {
    { Difficulty::Easy, { .replayCount = 2,
                        .octaveCount = 1,
                        .noteCount = 1,
                        .midiMin = 60,
                        .midiMax = 72
                       } },
    { Difficulty::Hard, {} },
    };

class NoteBuildController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit NoteBuildController(NotePlayer* player, QObject *parent = nullptr);
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
    NoteDifficultyConfig config = noteBuildDifficulty[Difficulty::Easy];
    GeneratedAudio result;
    QString getDescription() const override {
        return tr("Выберите нужную ноту");
    }
};

#endif // NOTEBUILDCONTROLLER_H
