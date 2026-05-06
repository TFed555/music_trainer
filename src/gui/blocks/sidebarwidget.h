#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include "../../core/common/models/exercisestrings.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QPushButton>

class SidebarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SidebarWidget(QWidget *parent = nullptr);
    ~SidebarWidget();
    void toggle();
    void close();
signals:
    void blockSelected(int block);
protected:
    void changeEvent(QEvent* event) override;
private:
    QVBoxLayout* rootLayout = nullptr;
    void clearButtons();
    void retranslate();
    QPushButton* addNavButton(const QString& title, BlockCategory block);
    void setLayout();
    QPropertyAnimation* anim;
    bool isOpen = false;
    QPushButton* activeBtn = nullptr;
};

#endif // SIDEBARWIDGET_H
