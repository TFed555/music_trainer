#include "intervalblockwidget.h"
#include "ui_intervalblockwidget.h"

IntervalBlockWidget::IntervalBlockWidget(QWidget *parent)
    : IBlockWidget(parent)
    , ui(new Ui::IntervalBlockWidget)
{
    ui->setupUi(this);
    connect(ui->exercise1Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(this, 1);
    });
    connect(ui->backBtn, &QPushButton::clicked, this, &IBlockWidget::backClicked);
}

IntervalBlockWidget::~IntervalBlockWidget()
{
    delete ui;
}
