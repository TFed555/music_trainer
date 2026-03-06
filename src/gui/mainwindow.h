#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "./blocks/mainmenuwidget.h"
#include "./blocks/IBlockWidget.h"
#include "../core/data/samples/sampleloader.h"
#include "../core/data/samples/samplerepository.h"
#include "../audio/audio.h"
#include "../audio/playback/noteplayer.h"
#include "../../core/sessions/common/isession.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
QString mainTitle = "Music trainer";
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void addBlock(IBlockWidget* block);
    void addExercise(IBlockWidget* block,QString title);
private:
    Ui::MainWindow *ui;
    QStackedWidget* stack;
    MainMenuWidget* mainMenu;
    QWidget* previousWidget = nullptr;
    QVector<IBlockWidget*> blocks;
    SampleLoader sampleLoader;
    SampleRepository sampleRepository;
    AudioProcessor* audio;
    NotePlayer* notePlayer;
    ISession* session;
    IExerciseWidget* exercise;
    QMetaObject::Connection sessionBackConn;
    QMetaObject::Connection exerciseBackConn;
};
#endif // MAINWINDOW_H
