#ifndef SESSIONREGISTRY_H
#define SESSIONREGISTRY_H

#include "sessionfactory.h"
#include "registry/intervalsessions.h"
#include "registry/chordsessions.h"
#include "registry/notesessions.h"
#include "../sessions/rhythm/rhythmrecognisesession.h"

inline void registerAllSessions(SessionFactory& factory) {
    registerIntervalSessions(factory);
    registerChordSessions(factory);
    registerNoteSessions(factory);
    // registerRhythmSessions(factory);



    factory.registerFactory(ExerciseType::RhythmRecognise,
                            [](NotePlayer* player, QObject* parent){
                                return std::make_unique<RhythmRecogniseSession>(player, parent);
                            });
}

#endif // SESSIONREGISTRY_H
