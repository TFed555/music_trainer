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
                           [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                               auto session = std::make_unique<TilesSession>(ExerciseType::IntervalRecognise, parent);
                               auto* ctrl = new IntervalRecogniseController(player, session.get());
                               auto* tilesctrl = new TilesController(player, session.get());
                               auto* view = new ExerciseWithTilesWidget(true, midi, nullptr);
                               session->setup(ctrl, tilesctrl, view, repo);
                               return session;
                           });
    factory.registerFactory(ExerciseType::IntervalIdentify,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>(ExerciseType::IntervalIdentify, parent);
                                auto* ctrl = new IntervalIdentifyController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view, repo);
                                return session;
                            });
    factory.registerFactory(ExerciseType::IntervalBuild,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<TilesSession>(ExerciseType::IntervalBuild, parent);
                                auto* ctrl = new IntervalBuildController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, midi, nullptr);
                                session->setup(ctrl, tilesctrl, view, repo);
                                return session;
                            });
    factory.registerFactory(ExerciseType::IntervalDirection,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>(ExerciseType::IntervalDirection, parent);
                                auto* ctrl = new IntervalDirectionController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view, repo);
                                return session;
                            });
}
#endif // INTERVALSESSIONS_H
