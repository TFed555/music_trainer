#include "exercisenotileswidget.h"
#include "ui_exercisenotileswidget.h"
#include <QTimer>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGroupBox>

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

void ExerciseNoTilesWidget::exercisePlayFinished() {
    btnsEnable(true);
}

void ExerciseNoTilesWidget::btnsEnable(bool status) {
    for (int i = 0; i < ui->answersLayout->count(); i++) {
        QLayoutItem* item = ui->answersLayout->itemAt(i);
        if (item && item->widget()) {
            QPushButton* btn = qobject_cast<QPushButton*>(item->widget());
            if (btn) {
                btn->setEnabled(status);
            }
        }
    }
}

void ExerciseNoTilesWidget::addAnswers(QVector<QString> answers) {
    ui->answersLayout->setHorizontalSpacing(10);
    ui->answersLayout->setVerticalSpacing(10);
    ui->answersLayout->setContentsMargins(20, 20, 20, 20);
    for (size_t i = 0; i < answers.size(); i++) {
        QPushButton* newBtn = new QPushButton();
        newBtn->setText(answers[i]);
        newBtn->setMinimumHeight(40);
        newBtn->setMinimumWidth(80);
        //TODO: создать файл стилей
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
        ui->answersLayout->addWidget(newBtn, i / 4, i % 4);
        newBtn->setDisabled(true);
        connect(newBtn, &QPushButton::clicked,
                this, [this, newBtn] () {
            selectedBtn = newBtn;
            highlightBtn(Mode::Input, newBtn);
            emit answerSelected(newBtn->text());
                });
    }
    update();
}

void ExerciseNoTilesWidget::highlightBtn(Mode mode, QPushButton* btn) {
    QString style = mode == Mode::Input ? "background-color: blue; color: white;" :
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
    "}";
    btn->setStyleSheet(style);
}

void ExerciseNoTilesWidget::showResult(const QString& correct) {
    for (size_t i = 0; i < ui->answersLayout->count(); i++) {
        QLayoutItem* item = ui->answersLayout->itemAt(i);
        if (item && item->widget()) {
            QPushButton* btn = qobject_cast<QPushButton*>(item->widget());
            if (btn) {
                QString answerText = btn->text();
                if (answerText == correct) {
                    btn->setStyleSheet(
                        "QPushButton {"
                        "   background-color: #4CAF50;"
                        "   color: white;"
                        "   border: 2px solid #45a049;"
                        "   border-radius: 5px;"
                        "}"
                        );
                }
            }
        }
    }
    resetSelection();
}

void ExerciseNoTilesWidget::resetSelection() {
    QTimer::singleShot(2000, this, [this]() {
        for (int i = 0; i < ui->answersLayout->count(); i++) {
            QLayoutItem* item = ui->answersLayout->itemAt(i);
            if (item && item->widget()) {
                QPushButton* btn = qobject_cast<QPushButton*>(item->widget());
                if (btn) {
                    btn->setStyleSheet(            "QPushButton {"
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
                                               "}");
                }
            }
        }
        selectedBtn = nullptr;
    });
    btnsEnable(false);
}

// void ExerciseNoTilesWidget::requestAnswerSlot()
// {
//     emit requestAnswers();
// }

void ExerciseNoTilesWidget::addDirectionSelector() {
    auto* group = new QGroupBox("Direction");
    auto* layout = new QHBoxLayout(group);
    auto* ascending  = new QRadioButton("Восходящий");
    auto* descending = new QRadioButton("Нисходящий");

    directionGroup = new QButtonGroup(this);
    directionGroup->addButton(ascending,  0);
    directionGroup->addButton(descending, 1);

    layout->addWidget(ascending);
    layout->addWidget(descending);

    ui->answersLayout->addWidget(group);

    connect(directionGroup, &QButtonGroup::idClicked,
            this, [this](int id) {
                emit directionSelected(id == 0 ? "Ascending" : "Descending");
    });
}
