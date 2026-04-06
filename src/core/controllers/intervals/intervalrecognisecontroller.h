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
    void noteSelected(const QString& noteName) override;
    void setDifficulty(int level) override;

private:
    void playTone() override;
private:
    int noteCounter;
    IntervalDifficultyConfig config = difficultyMap<IntervalDifficultyConfig>[Difficulty::Easy];
    static constexpr int intervalNoteCount = 2;
};

#endif // INTERVALRECOGNISECONTROLLER_H
