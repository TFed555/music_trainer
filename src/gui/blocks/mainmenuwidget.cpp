#include "mainmenuwidget.h"
#include "ui_mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);
    connect(ui->intervalBtn, &QPushButton::clicked, this, &MainMenuWidget::intervalClicked);
    connect(ui->chordBtn, &QPushButton::clicked, this, &MainMenuWidget::chordClicked);
    connect(ui->noteBtn, &QPushButton::clicked, this, &MainMenuWidget::noteClicked);
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}
