#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
#include "startwidget.h"
#include <QPropertyAnimation>
#include <QPushButton>

namespace Ui {
class SidebarWidget;
}

class SidebarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SidebarWidget(QWidget *parent = nullptr);
    ~SidebarWidget();
    void open();
signals:
    void blockSelected(int block);
private:
    QPushButton* addNavButton(const QString& title, StartWidget::BlockCategory block);
    void setLayout();
private:
    Ui::SidebarWidget *ui;
    QPropertyAnimation* anim;
    bool isOpen = false;
};

#endif // SIDEBARWIDGET_H
