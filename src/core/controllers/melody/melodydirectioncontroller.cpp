#include "melodydirectioncontroller.h"
#include "../../generators/melody/melodygenerator.h"

MelodyDirectionController::MelodyDirectionController(NotePlayer* player,
                                               QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
    setAnswerVariants();
    description = tr("Выберите направление мелодии");
}

void MelodyDirectionController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    MelodyGenerator gen(config);
    result = gen.generate();
    correctAnswer = result.direction;
    log(result.desc);
    playTask();
}

void MelodyDirectionController::setAnswerVariants() {
    answerVariants = [] (const QVector<MusicUtils::MelodyDirection>& keys) -> QVector<QString> {
        QVector<QString> result;
        result.reserve(keys.size());
        for (const auto& key : keys) {
            if (MusicUtils::melodyDirNames.contains(key)) {
                result.append(MusicUtils::melodyDirNames.value(key));
            }
        }
        return result;
    }(config.directions);
}

void MelodyDirectionController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playNotes(result.midiNotes);
}

void MelodyDirectionController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<MelodyDifficultyConfig>[dif];
    replayCount = config.replayCount;
    setAnswerVariants();
    giveAnswers();
}

void MelodyDirectionController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit attemptDone({
        .exerciseId = "melody.direction",
        .correctAnswer = correctAnswer,
        .userAnswer = userAnswer,
        .correct = (userAnswer == correctAnswer),
        .timestamp = QDateTime::currentDateTime()
    });
    emit showResult(correctAnswer);
}
