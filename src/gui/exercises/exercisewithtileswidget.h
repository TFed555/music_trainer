#ifndef EXERCISEWITHTILESWIDGET_H
#define EXERCISEWITHTILESWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../common/notetileswidget.h"

namespace Ui {
class ExerciseWithTilesWidget;
}

class ExerciseWithTilesWidget : public IExerciseWidget
{
    Q_OBJECT

public:
    explicit ExerciseWithTilesWidget(QWidget *parent = nullptr);
    ~ExerciseWithTilesWidget();

public slots:
    void showResult(const QVector<QString>& correct);
    void setMode(Mode m);
signals:
    void noteSelected(const QString& noteName);
private:
    Ui::ExerciseWithTilesWidget *ui;
    NoteTilesWidget *tiles;
};

#endif // EXERCISEWITHTILESWIDGET_H
