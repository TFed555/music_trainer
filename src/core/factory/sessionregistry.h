#ifndef SESSIONREGISTRY_H
#define SESSIONREGISTRY_H

#include "sessionfactory.h"
#include "registry/intervalsessions.h"
#include "registry/chordsessions.h"
#include "registry/notesessions.h"
#include "registry/rhythmsessions.h"

inline void registerAllSessions(SessionFactory& factory) {
    registerIntervalSessions(factory);
    registerChordSessions(factory);
    registerNoteSessions(factory);
    registerRhythmSessions(factory);
}

#endif // SESSIONREGISTRY_H
