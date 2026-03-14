#include "exercisenotileswidget.h"
#include "ui_exercisenotileswidget.h"
#include <QTimer>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGroupBox>
#include <QStyle>
#include <QComboBox>

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
    // connect(ui->difficultyBox, &QComboBox::activated,
    //         this, &ExerciseNoTilesWidget::difficultyChanged);
    connect(ui->difficultyBox, &QComboBox::currentIndexChanged,
            this, &ExerciseNoTilesWidget::difficultyChanged);
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
    for (int i = 0; i < answers.size(); i++) {
        QPushButton* newBtn = new QPushButton();
        newBtn->setObjectName("answerBtn");
        newBtn->setText(answers[i]);
        newBtn->setMinimumHeight(40);
        newBtn->setMinimumWidth(80);
        newBtn->setDisabled(true);

        ui->answersLayout->addWidget(newBtn, i / 4, i % 4);

        connect(newBtn, &QPushButton::clicked,
                this, [this, newBtn] () {
            selectedBtn = newBtn;
            for (auto* b : findChildren<QPushButton*>("answerBtn"))
                b->setProperty("selected", false);

            newBtn->setProperty("selected", true);
            refreshStyle(newBtn);

            emit answerSelected(newBtn->text());
        });
    }
    update();
}

void ExerciseNoTilesWidget::refreshStyle(QWidget* w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
}

void ExerciseNoTilesWidget::showResult(const QString& correct) {
    for (auto* btn : findChildren<QPushButton*>("answerBtn")) {
        btn->setProperty("selected", false);
        if (btn->text() == correct)
            btn->setProperty("result", "correct");
        else if (btn == selectedBtn)
            btn->setProperty("result", "wrong");
        refreshStyle(btn);
    }
    resetSelection();
}

void ExerciseNoTilesWidget::resetSelection() {
    QTimer::singleShot(2000, this, [this]() {
        for (auto* btn : findChildren<QPushButton*>("answerBtn")) {
            btn->setProperty("result", "");
            btn->setProperty("selected", false);
            refreshStyle(btn);
        }
        selectedBtn = nullptr;
        btnsEnable(false);
    });
}

void ExerciseNoTilesWidget::addDirectionSelector() {
    QGroupBox* group = new QGroupBox();
    QHBoxLayout* layout = new QHBoxLayout(group);
    group->setFixedSize(300, 100);
    QRadioButton* ascending  = new QRadioButton("Восходящий");
    QRadioButton* descending = new QRadioButton("Нисходящий");

    ascending->setProperty("direction", "Ascending");
    descending->setProperty("direction", "Descending");

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

void ExerciseNoTilesWidget::showDirectionResult(const QString& correct) {
    if (!directionGroup) return;
    for (auto* btn : directionGroup->buttons()) {
        QRadioButton* radio = qobject_cast<QRadioButton*>(btn);
        if (radio && radio->property("direction").toString() == correct) {
            radio->setStyleSheet("color: green; font-weight: bold;");
        }
    }
    resetSelection();
}
