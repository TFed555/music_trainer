#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include <QVBoxLayout>


class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();
    enum class BlockCategory {
        Intervals,
        Chords,
        Notes,
        Rhythm
    };
    void setBlock(int block);
signals:
    void exerciseSelected(ExerciseType);
private:
    void clearButtons();
    void addButton(const QString& title, ExerciseType type);
private:
    QVBoxLayout* layout;
};

#endif // STARTWIDGET_H
