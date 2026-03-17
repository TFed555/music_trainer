#include "startwidget.h"
#include <QPushButton>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->addStretch();
    setBlock(static_cast<int>(BlockCategory::Intervals));
}

StartWidget::~StartWidget()
{
}

void StartWidget::addButton(const QString& title, ExerciseType type) {
    QPushButton* btn = new QPushButton();
    btn->setText(title);
    btn->setFixedSize(300,30);
    layout->addWidget(btn,0,Qt::AlignCenter);
    connect(btn, &QPushButton::clicked, this, [this, type](){
        emit exerciseSelected(type);
    });
}

void StartWidget::setBlock(int block) {
    BlockCategory category = static_cast<BlockCategory>(block);
    clearButtons();
    switch(category) {
        case BlockCategory::Intervals:
            addButton("Определение интервала", ExerciseType::IntervalRecognise);
            addButton("Название интервала", ExerciseType::IntervalIdentify);
            addButton("Построение интервала",  ExerciseType::IntervalBuild);
            addButton("Направление интервала", ExerciseType::IntervalDirection);
            break;
        case BlockCategory::Chords:
            addButton("Определение типа аккорда", ExerciseType::ChordIdentify);
            addButton("Определение обращения аккорда", ExerciseType::ChordInversion);
            addButton("Определение основной ноты аккорда", ExerciseType::ChordRoot);
            addButton("Построение аккорда", ExerciseType::ChordBuild);
            break;
        case BlockCategory::Notes:
            addButton("Название ноты", ExerciseType::NoteBuild);
            addButton("Определение ноты", ExerciseType::NoteRecognise);
            addButton("Определение нот в мелодии", ExerciseType::NoteGuess);
            break;
    }
}

void StartWidget::clearButtons() {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}
