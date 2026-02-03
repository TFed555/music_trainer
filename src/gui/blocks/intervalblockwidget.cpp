#include "intervalblockwidget.h"
#include "ui_intervalblockwidget.h"

IntervalBlockWidget::IntervalBlockWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IntervalBlockWidget)
{
    ui->setupUi(this);
    connect(ui->exercise1Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(1);
    });
    connect(ui->backBtn, &QPushButton::clicked, this, &IntervalBlockWidget::backClicked);
}

IntervalBlockWidget::~IntervalBlockWidget()
{
    delete ui;
}
