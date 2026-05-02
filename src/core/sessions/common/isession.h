#ifndef ISESSION_H
#define ISESSION_H

#include <QObject>
#include "../../common/interfaces/IExerciseWidget.h"
#include "../../common/models/exercisestrings.h"

class ISession : public QObject
{
    Q_OBJECT
public:
    explicit ISession(ExerciseType type, QObject *parent = nullptr) : QObject(parent), exerciseType(type)
    {};
    virtual ~ISession() = default;
    virtual IExerciseWidget* getWidget() const { return view; };
    virtual QString title() const {
        return ExerciseStrings::displayName(exerciseType);
    }
signals:
    void back();
    void setDifficulty(int level);
protected:
    IExerciseWidget* view = nullptr;
    ExerciseType exerciseType;
};

#endif // ISESSION_H
