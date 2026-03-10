#include "chordrootcontroller.h"
#include "../../music/pitchutils.h"
#include "../../generators/chords/chordgenerator.h"

ChordRootController::ChordRootController(NotePlayer* player,
                                         QObject *parent)
    : IExerciseController(player, parent)
{
    connect(player, &NotePlayer::playbackFinished, this, [this]() {
        emit exercisePlayFinished();
    });
}

void ChordRootController::playTone() {
    correctAnswer.clear();
    userAnswer.clear();
    emit requestSetMode(Mode::Wait);
    ChordGenerator gen({.allowedTypes={MusicUtils::Chords::ChordType::Major, MusicUtils::Chords::ChordType::Minor},
                        .allowedInversions={MusicUtils::Chords::InversionType::Root}});
    auto result = gen.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    // correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[0]));
    correctAnswer.append(MusicUtils::midiToNote(result.midiNotes[1]));

    notePlayer->playChord(result.midiNotes);

}

void ChordRootController::noteSelected(const QString& name) {
    qDebug() << "Note selected" << name;
    userAnswer.append(name);
    if (correctAnswer.size() > 0) {
        emit showResult(correctAnswer, userAnswer);
        emit requestSetMode(Mode::Result);
        correctAnswer.clear();
    }
}
