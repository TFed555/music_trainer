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
    for (size_t i = 0; i < answers.size(); i++) {
        QPushButton* newBtn = new QPushButton();
        newBtn->setText(answers[i]);
        ui->horizontalLayout->addWidget(newBtn);
    }
    update();
}

void ExerciseNoTilesWidget::showResult(const QString& correct) {

}
