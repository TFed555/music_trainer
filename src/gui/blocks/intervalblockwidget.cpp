#include "intervalblockwidget.h"
#include "ui_intervalblockwidget.h"
#include "../exercises/intervalrecognisewidget.h"

IntervalBlockWidget::IntervalBlockWidget(QWidget *parent)
    : IBlockWidget(parent)
    , ui(new Ui::IntervalBlockWidget)
{
    ui->setupUi(this);

    exercises = {
        new IntervalRecogniseWidget(this)
    };

    connect(ui->exercise1Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(exercises[0]);
    });
    connect(ui->backBtn, &QPushButton::clicked, this, &IBlockWidget::backClicked);
}

IntervalBlockWidget::~IntervalBlockWidget()
{
    delete ui;
}
