#ifndef NOTESESSIONS_H
#define NOTESESSIONS_H
#include "sessionfactory.h"
#include "../sessions/common/tilessession.h"
#include "../sessions/common/notilessession.h"
#include "../controllers/notes/notebuildcontroller.h"
#include "../controllers/notes/noterecognisecontroller.h"
#include "../controllers/notes/noteguesscontroller.h"
#include "../controllers/melody/melodyrepeatcontroller.h"
#include "../controllers/melody/melodydirectioncontroller.h"
#include "../sessions/common/tilessession.h"
#include "../sessions/common/notilessession.h"

inline void registerNoteSessions(SessionFactory& factory) {
    factory.registerFactory(ExerciseType::NoteRecognise,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<TilesSession>(ExerciseType::NoteRecognise, parent);
                                auto* ctrl = new NoteRecogniseController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, midi, nullptr);
                                session->setup(ctrl, tilesctrl, view, repo);
                                return session;
                            });
    factory.registerFactory(ExerciseType::NoteBuild,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<TilesSession>(ExerciseType::NoteBuild, parent);
                                auto* ctrl = new NoteBuildController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(false, midi, nullptr);
                                session->setup(ctrl, tilesctrl, view, repo);
                                return session;
                            });
    factory.registerFactory(ExerciseType::NoteGuess,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>(ExerciseType::NoteGuess, parent);
                                auto* ctrl = new NoteGuessController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view, repo);
                                return session;
                            });

    factory.registerFactory(ExerciseType::MelodyRepeat,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<TilesSession>(ExerciseType::MelodyRepeat, parent);
                                auto* ctrl = new MelodyRepeatController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, midi, nullptr);
                                session->setup(ctrl, tilesctrl, view, repo);
                                return session;
                            });

    factory.registerFactory(ExerciseType::MelodyDirection,
                            [](NotePlayer* player, MidiInputManager* midi, StatisticsRepository* repo, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>(ExerciseType::MelodyDirection, parent);
                                auto* ctrl = new MelodyDirectionController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view, repo);
                                return session;
                            });
}
#endif // NOTESESSIONS_H
