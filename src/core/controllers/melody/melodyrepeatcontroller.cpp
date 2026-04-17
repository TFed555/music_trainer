#include "melodyrepeatcontroller.h"
#include "../../generators/melody/melodygenerator.h"

MelodyRepeatController::MelodyRepeatController(NotePlayer* player,
                                         QObject *parent)
    : ITilesExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
    description = tr("Повторите мелодию");
}

void MelodyRepeatController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    emit requestSetMode(Mode::Wait);
    MelodyGenerator gen(config);
    result = gen.generate();
    correctAnswer = [] (const QVector<int>& midiNotes) -> QVector<QString> {
        QVector<QString> res;
        res.reserve(midiNotes.size());
        for (auto& m : midiNotes) {
            res.append(MusicUtils::midiToNote(m));
        }
        return res;
    }(result.midiNotes);
    log(result.desc);
    playTask();
}

void MelodyRepeatController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void MelodyRepeatController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<MelodyDifficultyConfig>[dif];
    replayCount = config.replayCount;
    answerSize = config.noteCount;
    emit setOctaveCount(config.octaveCount);
}

void MelodyRepeatController::noteSelected(const QString& noteName, const bool listenOnly) {
    qDebug() << "Note selected" << noteName;
    if (listenOnly) return;
    userAnswer.append(noteName);
    if (userAnswer.size() == config.noteCount && correctAnswer.size() > 0) {
        emit attemptDone({
            .exerciseId = "melody.repeat",
            .correctAnswer = vecToStr(correctAnswer),
            .userAnswer = vecToStr(userAnswer),
            .correct = (userAnswer == correctAnswer),
            .timestamp = QDateTime::currentDateTime()
        });
        emit showResult(correctAnswer, userAnswer);
        emit requestSetMode(Mode::Result);
        correctAnswer.clear();
    }
}
