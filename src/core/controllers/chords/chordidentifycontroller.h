#ifndef CHORDIDENTIFYCONTROLLER_H
#define CHORDIDENTIFYCONTROLLER_H

#include "../common/iexercisecontroller.h"
#include "../../music/pitchutils.h"

class ChordIdentifyController : public IExerciseController
{
    Q_OBJECT
public:
    explicit ChordIdentifyController(NotePlayer* player, QObject *parent = nullptr);

public slots:
    void answerSelected(const QString& answer);
    void setDifficulty(int level) override;
signals:
    void showResult(const QString& correct);
private:
    void playTone() override;
private:
    QString correctAnswer;
    QString userAnswer;
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
};

#endif // CHORDIDENTIFYCONTROLLER_H
