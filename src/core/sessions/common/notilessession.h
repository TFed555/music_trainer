#ifndef NOTILESSESSION_H
#define NOTILESSESSION_H

#include "isession.h"
#include "../../controllers/common/ichoiceexercisecontroller.h"
#include "../../gui/exercises/exercisenotileswidget.h"
#include "../../data/statistics/statisticsrepository.h"

class NoTilesSession : public ISession
{
    Q_OBJECT
public:
    explicit NoTilesSession(ExerciseType type,
                          QObject* parent = nullptr)
        : ISession(type, parent) {

    };

    void setup(IChoiceExerciseController* ctrl, ExerciseNoTilesWidget* w, StatisticsRepository* statsRepo);
};

#endif // NOTILESSESSION_H
