#ifndef TILESSESSION_H
#define TILESSESSION_H

#include "isession.h"
#include "../../controllers/common/itilesexercisecontroller.h"
#include "../../gui/exercises/exercisewithtileswidget.h"
#include "../core/controllers/common/tilescontroller.h"

class TilesSession : public ISession
{
    Q_OBJECT
public:
    explicit TilesSession(const QString& sessionTitle,
                        QObject* parent = nullptr)
    : ISession(parent), _title(sessionTitle) {

    };

    void configure(std::function<void()> fn) {
        fn();
    }

    void setup(ITilesExerciseController* ctrl, TilesController* tilesctrl, ExerciseWithTilesWidget* w);
    QString title() const override { return _title;}
private:
    QString _title;
};

#endif // TILESSESSION_H
