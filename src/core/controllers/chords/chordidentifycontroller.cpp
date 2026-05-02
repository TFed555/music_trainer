#include "chordidentifycontroller.h"
#include "../../generators/chords/chordgenerator.h"

ChordIdentifyController::ChordIdentifyController(NotePlayer* player,
                                                       QObject *parent)
    : IChoiceExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void ChordIdentifyController::generateTask() {
    correctAnswer.clear();
    userAnswer.clear();
    ChordGenerator gen(config);
    result = gen.generate();
    correctAnswer = result.type;
    log(result.desc);
    playTask();
}

void ChordIdentifyController::playTask() {
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    notePlayer->playChord(result.midiNotes);
}

void ChordIdentifyController::answerSelected(const QString& answer){
    userAnswer = answer;
    emit attemptDone({
        .exerciseId = "chord.identify",
        .correctAnswer = correctAnswer,
        .userAnswer = userAnswer,
        .correct = (userAnswer == correctAnswer),
        .timestamp = QDateTime::currentDateTime()
    });
    emit showResult(correctAnswer);
}

void ChordIdentifyController::setDifficulty(int level) {
    Difficulty dif = static_cast<Difficulty>(level);
    config = difficultyMap<ChordDifficultyConfig>[dif];
    qDebug() << level;
    if (level > 0) {
        config.allowedTypes.append(MusicUtils::Chords::ChordType::MajorSeventhChord);
        config.allowedTypes.append(MusicUtils::Chords::ChordType::MinorSeventhChord);
        config.allowedTypes.append(MusicUtils::Chords::ChordType::AugmentedTriad);
        config.allowedTypes.append(MusicUtils::Chords::ChordType::DiminishedTriad);
    }
    config.allowedInversions = {MusicUtils::Chords::InversionType::Root};
    replayCount = config.replayCount;
    giveAnswers();
}

