#ifndef INTERVALEXERCISEWIDGET_H
#define INTERVALEXERCISEWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../common/notetileswidget.h"

namespace Ui {
class IntervalExerciseWidget;
}

class IntervalExerciseWidget : public IExerciseWidget
{
    Q_OBJECT

public:
    explicit IntervalExerciseWidget(QWidget *parent = nullptr);
    ~IntervalExerciseWidget();

    QString title() const override { return "Распознавание интервала"; }

public slots:
    void showResult(const QVector<QString>& correct);
    void setMode(Mode m);
private:
    Ui::IntervalExerciseWidget *ui;
    NoteTilesWidget *tiles;
};

#endif // INTERVALEXERCISEWIDGET_H
