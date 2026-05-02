#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTranslator>
#include "../core/data/samples/sampleloader.h"
#include "../core/data/samples/samplerepository.h"
#include "../core/data/statistics/statisticsloader.h"
#include "../core/data/statistics/statisticsrepository.h"
#include "../audio/audio.h"
#include "../audio/playback/noteplayer.h"
#include "../../core/sessions/common/isession.h"
#include "../core/factory/sessionfactory.h"
#include "./blocks/startwidget.h"
#include "./blocks/sidebarwidget.h"
#include "./common/statswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
QString mainTitle = "Тренажер музыкального слуха";
public:
    MainWindow(SessionFactory& factory, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void showStats();
    void setLanguage(const QString& lang);
private:
    void startExercise(ExerciseType);
    void changeEvent(QEvent* event) override;
    void retranslateUi();
private:
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
    StatisticsLoader statsLoader;
    StatisticsRepository statsRepository;
    QMetaObject::Connection sessionBackConn;
    SessionFactory& sessionFactory;
    StatsWidget* stats;
    QTranslator translator;
    QMenu* settingsMenu;
    QMenu* helpMenu;
    QMenu* langMenu;
    QAction* statsAction;
    QAction* exitAction;
};
#endif // MAINWINDOW_H
