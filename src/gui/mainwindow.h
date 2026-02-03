#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "./blocks/mainmenuwidget.h"
#include "./blocks/intervalblockwidget.h"
#include "./exercises/intervalexercisewidget.h"

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
    void openIntervalExercise(int id);

private:
    Ui::MainWindow *ui;
    QStackedWidget* stack;
    MainMenuWidget* mainMenu;
    IntervalBlockWidget* intervalBlock;
    IntervalExerciseWidget *intervalExercise;
};
#endif // MAINWINDOW_H
