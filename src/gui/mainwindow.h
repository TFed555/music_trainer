#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../core/data/samples/sampleloader.h"
#include "../core/data/samples/samplerepository.h"
#include "../audio/audio.h"
#include "../audio/playback/noteplayer.h"
#include "../../core/sessions/common/isession.h"
#include "../core/factory/sessionfactory.h"
#include "./blocks/startwidget.h"
#include "./blocks/sidebarwidget.h"

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
    MainWindow(SessionFactory& factory, QWidget *parent = nullptr);
    ~MainWindow();
private:
    void startExercise(ExerciseType);
private:
    Ui::MainWindow *ui;
    QStackedWidget* stack;
    QWidget* previousWidget = nullptr;
    StartWidget* startMenu;
    SidebarWidget* sidebar;
    SampleLoader sampleLoader;
    SampleRepository sampleRepository;
    AudioProcessor* audio;
    NotePlayer* notePlayer;
    QScopedPointer<ISession> session;
    IExerciseWidget* exercise;
    QMetaObject::Connection sessionBackConn;
    QMetaObject::Connection exerciseBackConn;
    SessionFactory& sessionFactory;
};
#endif // MAINWINDOW_H
