#include "intervalblockwidget.h"
#include "ui_intervalblockwidget.h"

IntervalBlockWidget::IntervalBlockWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IntervalBlockWidget)
{
    ui->setupUi(this);
}

IntervalBlockWidget::~IntervalBlockWidget()
{
    delete ui;
}
