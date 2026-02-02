#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "mainmenuwidget.h"
#include "intervalblockwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMainMenu();
    void showIntervalBlock();

private:
    Ui::MainWindow *ui;
    QStackedWidget* stack;
    MainMenuWidget* mainMenu;
    IntervalBlockWidget* intervalBlock;
};
#endif // MAINWINDOW_H
