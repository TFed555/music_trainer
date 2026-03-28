#ifndef RHYTHMSESSIONS_H
#define RHYTHMSESSIONS_H

#include "sessionfactory.h"
#include "../sessions/rhythm/rhythmsession.h"
#include "../controllers/rhythm/rhythmrecognisecontroller.h"

inline void registerRhythmSessions(SessionFactory& factory) {
    factory.registerFactory(ExerciseType::RhythmRecognise,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<RhythmSession>("Определение ритма", parent);
                                auto* ctrl = new RhythmRecogniseController(player, session.get());
                                auto* view = new ExerciseRhythmWidget(nullptr);
                                session->setup(ctrl, view);
                                return session;
                            });
}

#endif // RHYTHMSESSIONS_H
