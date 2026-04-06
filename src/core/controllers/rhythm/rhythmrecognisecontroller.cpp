#include "rhythmrecognisecontroller.h"
#include "../../generators/rhythm/rhythmgenerator.h"
#include <QTimer>

RhythmRecogniseController::RhythmRecogniseController(NotePlayer* player,
                                                     QObject *parent)
    : IRhythmExerciseController(player, PlaybackendSignal::PlaybackFinished, parent)
{
}

void RhythmRecogniseController::playTone() {
    using namespace MusicUtils::Rhythm;
    RhythmGenerator generator(config);
    auto result = generator.generate();
    log(result.desc);
    qDebug() << playbackLog.last().timestamp << " " << playbackLog.last().desc;
    QVector<RhythmType> rhythmTypes;
    for (auto b : result.userBeats) {
        rhythmTypes.append(rhythmTypeNames[b.duration]);
    }
    emit setRhythmNotes(rhythmTypes, result.bpm);
    lastBeats = result;
    notePlayer->playBeat(result);
    playbackCount = 3;
}

void RhythmRecogniseController::setDifficulty(int level) {

}

void RhythmRecogniseController::onPlaybackFinished() {
    playbackCount--;
    if (playbackCount <= 0) return;
    emit exercisePlayFinished();
    notePlayer->playMetronome(lastBeats);
}

void RhythmRecogniseController::setConfig(const QMap<int,int>& states) {
    QVector<int> allowedDurations;
    for (int i : states.keys()) {
        if (states[i] > 0){
            allowedDurations.append(i);
        }
    }
    config = {8.0f, allowedDurations, 80};
    qDebug() << allowedDurations;
}

void RhythmRecogniseController::bpmChanged(const int& bpm) {
    this->bpm = bpm;
    config.bpm = bpm;
    qDebug() << bpm;
}

void RhythmRecogniseController::inputFinished(const QVector<int>& notePoses, const QVector<int>& userTaps) {
    QSet<int> matched;
    int wrong = 0;
    int correct = 0;
    for (int tap : userTaps) {
        int bestIdx = -1;
        int bestDist = INT_MAX;
        for (int i = 0; i < notePoses.size(); i++) {
            if (matched.contains(i)) continue;
            int dist = std::abs(tap-notePoses[i]);
            if (dist < bestDist) {
                bestDist = dist;
                bestIdx = i;
            }
        }
    if (bestIdx != -1 && bestDist <= treshold) {
        matched.insert(bestIdx);
        correct++;
    }
    }
    wrong = userTaps.size() - correct;
    // int missed = notePoses.size() - correct;
    emit result(correct, wrong);
}

