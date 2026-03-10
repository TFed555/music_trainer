#include "chordblockwidget.h"
#include "ui_chordblockwidget.h"

ChordBlockWidget::ChordBlockWidget(QWidget *parent)
    : IBlockWidget(parent)
    , ui(new Ui::ChordBlockWidget)
{
    ui->setupUi(this);

    connect(ui->exercise1Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::ChordIdentify, this);
    });
    connect(ui->exercise2Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::ChordInversion, this);
    });
    connect(ui->exercise3Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::ChordRoot, this);
    });
    connect(ui->backBtn, &QPushButton::clicked, this, &IBlockWidget::backClicked);
}

ChordBlockWidget::~ChordBlockWidget()
{
    delete ui;
}
