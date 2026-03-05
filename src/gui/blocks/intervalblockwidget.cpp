#include "intervalblockwidget.h"
#include "ui_intervalblockwidget.h"

IntervalBlockWidget::IntervalBlockWidget(QWidget *parent)
    : IBlockWidget(parent)
    , ui(new Ui::IntervalBlockWidget)
{
    ui->setupUi(this);


    connect(ui->exercise1Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::IntervalRecognise, this);
    });
    connect(ui->exercise2Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::IntervalIdentify, this);
    });
    connect(ui->exercise3Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::IntervalBuild, this);
    });
    connect(ui->exercise4Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::IntervalDirection, this);
    });
    connect(ui->backBtn, &QPushButton::clicked, this, &IBlockWidget::backClicked);
}

IntervalBlockWidget::~IntervalBlockWidget()
{
    delete ui;
}
