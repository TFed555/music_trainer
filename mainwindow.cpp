#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../audio/generators/IntervalGenerator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    processor = new AudioProcessor(this);
    connect(processor, &AudioProcessor::playbackFinished,
            this, []() { qDebug() << "Playback finished"; });
    connect(processor, &AudioProcessor::err,
            this, [](const QString& msg) { qDebug() << "Error:" << msg; });
    connect(ui->playBtn, &QPushButton::clicked, this, &MainWindow::playTone);
    connect(ui->stopBtn, &QPushButton::clicked, processor, &AudioProcessor::stopPlayback);
    connect(processor, &AudioProcessor::notePlayed,
            this, [](const QString& note) {
                qDebug() << "Played:" << note;
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playTone() {
    processor->setGenerator(std::make_unique<IntervalGenerator>());
    processor->play(2.0f);
}
