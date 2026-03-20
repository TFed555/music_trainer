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
    void noteSelected(const QString& noteName) override;
    void setDifficulty(int level) override;
signals:
    void showResult(QVector<QString> answer, QVector<QString> selected);
    void setQuestion(const QString& question);
    void highlightQuestion(QVector<QString> notes);
private:
    void playTone() override;
private:
    int noteCounter = 0;
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
};

#endif // CHORDBUILDCONTROLLER_H
