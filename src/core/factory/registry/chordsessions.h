#ifndef CHORDSESSIONS_H
#define CHORDSESSIONS_H
#include "sessionfactory.h"
#include "../sessions/common/tilessession.h"
#include "../sessions/common/notilessession.h"
#include "../controllers/chords/chordbuildcontroller.h"
#include "../controllers/chords/chordrootcontroller.h"
#include "../controllers/chords/chordidentifycontroller.h"
#include "../controllers/chords/chordinversioncontroller.h"

inline void registerChordSessions(SessionFactory& factory) {
    factory.registerFactory(ExerciseType::ChordIdentify,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>("Определение аккорда", parent);
                                auto* ctrl = new ChordIdentifyController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::ChordInversion,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>("Обращение аккорда", parent);
                                auto* ctrl = new ChordInversionController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::ChordRoot,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<TilesSession>("Определение основной ноты аккорда", parent);
                                auto* ctrl = new ChordRootController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, nullptr);
                                session->setup(ctrl, tilesctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::ChordBuild,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<TilesSession>("Построение аккорда", parent);
                                auto* ctrl = new ChordBuildController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, nullptr);
                                session->setup(ctrl, tilesctrl, view);
                                return session;
                            });
}

#endif // CHORDSESSIONS_H
