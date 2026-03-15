#ifndef SESSIONREGISTRY_H
#define SESSIONREGISTRY_H

#include "sessionfactory.h"
#include "../sessions/intervals/intervalrecognisesession.h"
#include "../sessions/intervals/intervalidentifysession.h"
#include "../sessions/intervals/intervalbuildsession.h"
#include "../sessions/intervals/intervaldirectionsession.h"
#include "../sessions/chords/chordidentifysession.h"
#include "../sessions/chords/chordinversionsession.h"
#include "../sessions/chords/chordrootsession.h"
#include "../sessions/chords/chordbuildsession.h"
#include "../sessions/notes/noterecognisesession.h"
#include "../sessions/notes/notebuildsession.h"
#include "../sessions/notes/noteguesssession.h"

inline void registerAllSessions(SessionFactory& factory) {
    factory.registerFactory(ExerciseType::IntervalRecognise,
                    [](NotePlayer* player, QObject* parent){
                    return std::make_unique<IntervalRecogniseSession>(player, parent);
    });
    factory.registerFactory(ExerciseType::IntervalIdentify,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<IntervalIdentifySession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::IntervalBuild,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<IntervalBuildSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::IntervalDirection,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<IntervalDirectionSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::ChordIdentify,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<ChordIdentifySession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::ChordInversion,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<ChordInversionSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::ChordRoot,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<ChordRootSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::ChordBuild,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<ChordBuildSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::NoteRecognise,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<NoteRecogniseSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::NoteBuild,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<NoteBuildSession>(player, parent);
                            });
    factory.registerFactory(ExerciseType::NoteGuess,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<NoteGuessSession>(player, parent);
                            });
}

#endif // SESSIONREGISTRY_H
