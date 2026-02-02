#include "mainmenuwidget.h"
#include "ui_mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    connect(ui->intervalBtn, &QPushButton::clicked, this, &MainMenuWidget::intervalClicked);
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}
