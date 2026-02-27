#ifndef IBLOCKWIDGET_H
#define IBLOCKWIDGET_H
#pragma once
#include <QWidget>

class IBlockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IBlockWidget(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IBlockWidget() {};
signals:
    void backClicked();
    void exerciseSelected(QWidget* exercise);
    void exerciseBackClicked();
};

#endif // IBLOCKWIDGET_H
