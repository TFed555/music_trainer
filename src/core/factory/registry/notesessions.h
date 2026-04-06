#ifndef NOTESESSIONS_H
#define NOTESESSIONS_H
#include "sessionfactory.h"
#include "../sessions/common/tilessession.h"
#include "../sessions/common/notilessession.h"
#include "../controllers/notes/notebuildcontroller.h"
#include "../controllers/notes/noterecognisecontroller.h"
#include "../controllers/notes/noteguesscontroller.h"
#include "../sessions/common/tilessession.h"
#include "../sessions/common/notilessession.h"

inline void registerNoteSessions(SessionFactory& factory) {
    factory.registerFactory(ExerciseType::NoteRecognise,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<TilesSession>("Определение ноты", parent);
                                auto* ctrl = new NoteRecogniseController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(true, nullptr);
                                session->setup(ctrl, tilesctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::NoteBuild,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<TilesSession>("Название ноты", parent);
                                auto* ctrl = new NoteBuildController(player, session.get());
                                auto* tilesctrl = new TilesController(player, session.get());
                                auto* view = new ExerciseWithTilesWidget(false, nullptr);
                                session->setup(ctrl, tilesctrl, view);
                                return session;
                            });
    factory.registerFactory(ExerciseType::NoteGuess,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>("Определение нот в мелодии", parent);
                                auto* ctrl = new NoteGuessController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view);
                                return session;
                            });
}
#endif // NOTESESSIONS_H
