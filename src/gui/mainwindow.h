#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "./blocks/mainmenuwidget.h"
#include "./exercises/intervalexercisewidget.h"
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

private slots:
    void openExercise(IBlockWidget* block, int id);

private:
    void addBlock(IBlockWidget* block);

private:
    Ui::MainWindow *ui;
    QStackedWidget* stack;
    MainMenuWidget* mainMenu;

    IntervalExerciseWidget *intervalExercise;

    SampleLoader sampleLoader;
    SampleRepository sampleRepository;
    AudioProcessor* audio;
    NotePlayer* notePlayer;
    QWidget* previousWidget = nullptr;
    QVector<IBlockWidget*> blocks;
};
#endif // MAINWINDOW_H
