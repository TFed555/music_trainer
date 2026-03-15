#ifndef IBLOCKWIDGET_H
#define IBLOCKWIDGET_H
#pragma once
#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"

class IBlockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IBlockWidget(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IBlockWidget() {};
    enum class BlockCategory {
        Intervals,
        Chords,
        Notes
    };
signals:
    void backClicked();
    void exerciseSelected(ExerciseType, IBlockWidget*);
};

#endif // IBLOCKWIDGET_H
