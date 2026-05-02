#ifndef CHORDIDENTIFYCONTROLLER_H
#define CHORDIDENTIFYCONTROLLER_H

#include "../common/ichoiceexercisecontroller.h"

class ChordIdentifyController : public IChoiceExerciseController
{
    Q_OBJECT
public:
    explicit ChordIdentifyController(NotePlayer* player, QObject *parent = nullptr);

public slots:
    void answerSelected(const QString& answer) override;
    void setDifficulty(int level) override;
private:
    void generateTask() override;
    void playTask() override;
private:
    ChordDifficultyConfig config = difficultyMap<ChordDifficultyConfig>[Difficulty::Easy];
    GeneratedChord result;
    QString getDescription() const override {
        return tr("Определите тип аккорда");
    }
    QVector<QString> getAnswerVariants() const override {
        return MusicUtils::toNameVector(config.allowedTypes, MusicUtils::Chords::chordName);
    }
};

#endif // CHORDIDENTIFYCONTROLLER_H
