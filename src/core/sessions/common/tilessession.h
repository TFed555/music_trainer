#ifndef TILESSESSION_H
#define TILESSESSION_H

#include "isession.h"
#include "../../controllers/common/itilesexercisecontroller.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/common/tilescontroller.h"
#include "../../data/statistics/statisticsrepository.h"

class TilesSession : public ISession
{
    Q_OBJECT
public:
    explicit TilesSession(ExerciseType type,
                        QObject* parent = nullptr)
    : ISession(type, parent){

    };

    void setup(ITilesExerciseController* ctrl, TilesController* tilesctrl,
               ExerciseWithTilesWidget* w, StatisticsRepository* statsRepo);
};

#endif // TILESSESSION_H
