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
                                session->configure([ctrl, view] () {
                                    QObject::connect(ctrl, &NoteBuildController::setQuestion,
                                                     view, &ExerciseWithTilesWidget::setQuestion);

                                    QObject::connect(ctrl, &NoteBuildController::setOctaveCount,
                                                     view, &ExerciseWithTilesWidget::setOctaveCount);

                                    ctrl->setDifficulty(0);
                                });
                                return session;
                            });
    factory.registerFactory(ExerciseType::NoteGuess,
                            [](NotePlayer* player, QObject* parent){
                                auto session = std::make_unique<NoTilesSession>("Определение нот в мелодии", parent);
                                auto* ctrl = new NoteGuessController(player, session.get());
                                auto* view = new ExerciseNoTilesWidget(nullptr);
                                session->setup(ctrl, view);
                                session->configure([ctrl, view] () {
                                    QObject::connect(ctrl, &NoteGuessController::showResult,
                                                     view, &ExerciseNoTilesWidget::showResult);

                                    QObject::connect(view, &ExerciseNoTilesWidget::answerSelected,
                                                     ctrl, &NoteGuessController::answerSelected);

                                    QObject::connect(ctrl, &NoteGuessController::setAnswers,
                                                     view, &ExerciseNoTilesWidget::addAnswers);
                                    ctrl->giveAnswers();
                                });
                                return session;
                            });
}
#endif // NOTESESSIONS_H
