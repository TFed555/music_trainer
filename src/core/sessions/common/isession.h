#ifndef ISESSION_H
#define ISESSION_H

#include <QObject>
#include "../../common/interfaces/IExerciseWidget.h"

class ISession : public QObject
{
    Q_OBJECT
public:
    explicit ISession(QObject *parent = nullptr) : QObject(parent) {};
    virtual ~ISession() = default;
    virtual IExerciseWidget* getWidget() const = 0;
    virtual QString title() const = 0;
signals:
    void back();
    void setDifficulty(int level);
};

#endif // ISESSION_H
