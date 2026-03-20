#ifndef NOTERECOGNISECONTROLLER_H
#define NOTERECOGNISECONTROLLER_H

#include "../common/itilesexercisecontroller.h"

static inline const QMap<Difficulty, NoteDifficultyConfig> noteRecogniseDifficulty = {
    { Difficulty::Easy, {1, 1, 60, 72} },
    { Difficulty::Hard, {} },
    };

class NoteRecogniseController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit NoteRecogniseController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& noteName) override;
    void setDifficulty(int level) override;
signals:
    void showResult(QVector<QString> answer, QVector<QString> selected);
private:
    void playTone() override;
private:
    NoteDifficultyConfig config = noteRecogniseDifficulty[Difficulty::Easy];
};

#endif // NOTERECOGNISECONTROLLER_H
