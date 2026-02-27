#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "./blocks/mainmenuwidget.h"
#include "./blocks/IBlockWidget.h"

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

private:
    void addBlock(IBlockWidget* block);

private:
    Ui::MainWindow *ui;
    QStackedWidget* stack;
    MainMenuWidget* mainMenu;
    QWidget* previousWidget = nullptr;
    QVector<IBlockWidget*> blocks;
};
#endif // MAINWINDOW_H
