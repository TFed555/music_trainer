#ifndef IEXERCISEWIDGET_H
#define IEXERCISEWIDGET_H

#include <QWidget>
#include "../models/Mode.h"

enum class ExerciseType {
    IntervalRecognise,
    IntervalIdentify,
    IntervalBuild,
    IntervalDirection
};

class IExerciseWidget : public QWidget {
    Q_OBJECT
public:
    explicit IExerciseWidget(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IExerciseWidget() {};
public slots:
    virtual void exercisePlayFinished() = 0;
signals:
    void startClicked();
    void stopClicked();
    void requestSetMode(Mode);
    void backClicked();
};

#endif // IEXERCISEWIDGET_H
