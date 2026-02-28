#include "intervalexercisewidget.h"
#include "ui_intervalexercisewidget.h"
#include <QEventLoop>
#include <QTimer>

IntervalExerciseWidget::IntervalExerciseWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::IntervalExerciseWidget)
    , tiles(new NoteTilesWidget(this))
{
    ui->setupUi(this);
    // auto* tiles = new NoteTilesWidget(this);
    ui->horizontalLayout->addWidget(tiles);
    connect(ui->startBtn, &QPushButton::clicked, this, &IntervalExerciseWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &IntervalExerciseWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
}

IntervalExerciseWidget::~IntervalExerciseWidget()
{
    delete ui;
}

void IntervalExerciseWidget::showResult(const QVector<QString>& correct) {
    tiles->highlight(correct);
    QTimer::singleShot(2000, this, [this]() {
        emit requestSetMode(Mode::Input);
    });
}

void IntervalExerciseWidget::setMode(Mode m) {
    tiles->setMode(m);
}
