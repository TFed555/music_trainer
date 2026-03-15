#ifndef CHORDROOTCONTROLLER_H
#define CHORDROOTCONTROLLER_H

#include "../common/itilesexercisecontroller.h"

class ChordRootController : public ITilesExerciseController
{
    Q_OBJECT
public:
    explicit ChordRootController(NotePlayer* player, QObject *parent = nullptr);
public slots:
    void noteSelected(const QString& name) override;
    void setDifficulty(int level) override;
signals:
    void requestSetMode(Mode);
    void showResult(QVector<QString> answer, QVector<QString> selected);
private:
    void playTone() override;
private:
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
};

#endif // CHORDROOTCONTROLLER_H
