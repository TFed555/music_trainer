#include "exercisenotileswidget.h"
#include "ui_exercisenotileswidget.h"

ExerciseNoTilesWidget::ExerciseNoTilesWidget(QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseNoTilesWidget)
{
    ui->setupUi(this);

    connect(ui->startBtn, &QPushButton::clicked, this, &ExerciseNoTilesWidget::startClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseNoTilesWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, [this] (){
        emit backClicked();
    });
}

ExerciseNoTilesWidget::~ExerciseNoTilesWidget()
{
    delete ui;
}

void ExerciseNoTilesWidget::addAnswers(QVector<QString> answers) {
    ui->gridLayout->setHorizontalSpacing(150);
    ui->gridLayout->setVerticalSpacing(80);
    ui->gridLayout->setContentsMargins(20, 20, 20, 20);
    for (size_t i = 0; i < answers.size(); i++) {
        QPushButton* newBtn = new QPushButton();
        newBtn->setText(answers[i]);
        newBtn->setMinimumHeight(40);
        newBtn->setMinimumWidth(120);
        newBtn->setStyleSheet(
            "QPushButton {"
            "   background-color: #f0f0f0;"
            "   border: 1px solid #ccc;"
            "   border-radius: 5px;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #e0e0e0;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #d0d0d0;"
            "}"
            );
        ui->gridLayout->addWidget(newBtn, i / 4, i % 4);
    }
    update();
}

void ExerciseNoTilesWidget::showResult(const QString& correct) {

}

void ExerciseNoTilesWidget::requestAnswerSlot()
{
    emit requestAnswers();
}
