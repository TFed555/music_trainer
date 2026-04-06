#ifndef INTERVALSESSIONS_H
#define INTERVALSESSIONS_H
#include "sessionfactory.h"
#include "../controllers/intervals/intervalrecognisecontroller.h"
#include "../controllers/intervals/intervalbuildcontroller.h"
#include "../controllers/intervals/intervalidentifycontroller.h"
#include "../controllers/intervals/intervaldirectioncontroller.h"
#include "../sessions/common/tilessession.h"
#include "../sessions/common/notilessession.h"

inline void registerIntervalSessions(SessionFactory& factory) {
    factory.registerFactory(ExerciseType::IntervalRecognise,
                           [](NotePlayer* player, QObject* parent){
                               auto session = std::make_unique<TilesSession>("Определение интервала", parent);
                               auto* ctrl = new IntervalRecogniseController(player, session.get());
                               auto* tilesctrl = new TilesController(player, session.get());
                               auto* view = new ExerciseWithTilesWidget(true, nullptr);
                               session->setup(ctrl, tilesctrl, view);
                               return session;
                           });
    factory.registerFactory(ExerciseType::IntervalIdentify,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>("Определение названия интервала", parent);
                                auto* ctrl = new IntervalIdentifyController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::IntervalBuild,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<TilesSession>("Построение интервала", parent);
                                auto* ctrl = new IntervalBuildController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, nullptr);
                                session->setup(ctrl, tilesctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::IntervalDirection,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>("Определение направления интервала", parent);
                                auto* ctrl = new IntervalDirectionController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view);
                                return session;
                            });
}
#endif // INTERVALSESSIONS_H
