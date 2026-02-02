#ifndef EXERCISEWIDGET_H
#define EXERCISEWIDGET_H

#include <QWidget>

class ExerciseWidget : public QWidget {
    Q_OBJECT
public:
    virtual void startExercise() = 0;
    virtual void stopExercise() = 0;
};

#endif // EXERCISEWIDGET_H
