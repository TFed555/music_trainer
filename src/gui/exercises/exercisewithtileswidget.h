#ifndef EXERCISEWITHTILESWIDGET_H
#define EXERCISEWITHTILESWIDGET_H

#include <QWidget>
#include <QLabel>

#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../common/octavetileswidget.h"

namespace Ui {
class ExerciseWithTilesWidget;
}

class ExerciseWithTilesWidget : public IExerciseWidget
{
    Q_OBJECT

public:
    explicit ExerciseWithTilesWidget(bool noteNamesVisible = true, QWidget *parent = nullptr);
    ~ExerciseWithTilesWidget();

public slots:
    void showResult(const QVector<QString>& correct, const QVector<QString>& selected);
    void setMode(Mode m);
    void exercisePlayFinished() override;
    void setQuestion(const QString&);
    void highlightQuestion(QVector<QString> notes);
    void setOctaveCount(int count);
signals:
    void noteSelected(const QString& noteName);
    void resetTiles();
    void difficultyChanged(int level);
private:
    Ui::ExerciseWithTilesWidget *ui;
    OctaveTilesWidget *tiles;
    QLabel* questionLabel = nullptr;
};

#endif // EXERCISEWITHTILESWIDGET_H
