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
}

#endif // SESSIONREGISTRY_H
