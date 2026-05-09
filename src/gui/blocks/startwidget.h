#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../../core/common/models/exercisestrings.h"
#include <QVBoxLayout>
#include <QCoreApplication>

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

    void setBlock(int block);
signals:
    void exerciseSelected(ExerciseType);
protected:
    void changeEvent(QEvent* event) override;
private:
    void clearButtons();
    QVBoxLayout* rootLayout = nullptr;
    int currentBlock;
};

#endif // STARTWIDGET_H
