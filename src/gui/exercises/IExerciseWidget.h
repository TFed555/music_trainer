#ifndef IEXERCISEWIDGET_H
#define IEXERCISEWIDGET_H

#include <QWidget>
#include "../common/notetileswidget.h"

class IExerciseWidget : public QWidget {
    Q_OBJECT
public:
    explicit IExerciseWidget(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IExerciseWidget() {};
    virtual QString title() const = 0;

    QVector<QString> correctAnswer;
    QVector<QString>  userAnswer;
signals:
    void start();
    void stop();
    void inputFinished();
    void requestSetMode(NoteTilesWidget::Mode);
    void backClicked();
};

#endif // IEXERCISEWIDGET_H
