#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>
#include "startwidget.h"
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
    void retranslate();
    QPushButton* intervalsBtn;
    QPushButton* chordsBtn;
    QPushButton* notesBtn;
    QPushButton* rhythmBtn;
    QPushButton* melodyBtn;
    QPushButton* addNavButton(const QString& title, StartWidget::BlockCategory block);
    void setLayout();
    QPropertyAnimation* anim;
    bool isOpen = false;
};

#endif // SIDEBARWIDGET_H
