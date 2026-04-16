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

const QMap<StartWidget::BlockCategory, StartWidget::BlockConfig>& StartWidget::blockConfigs() {
    static const QMap<BlockCategory, BlockConfig> configs = {
            { BlockCategory::Intervals, {
                                     { "Определение интервала",  ExerciseType::IntervalRecognise },
                                     { "Название интервала",     ExerciseType::IntervalIdentify  },
                                     { "Построение интервала",   ExerciseType::IntervalBuild},
                                     { "Направление интервала",  ExerciseType::IntervalDirection },
                                     }},
            { BlockCategory::Chords, {
                                  { "Определение типа аккорда", ExerciseType::ChordIdentify  },
                                  { "Определение обращения аккорда", ExerciseType::ChordInversion },
                                  { "Определение основной ноты аккорда", ExerciseType::ChordRoot},
                                  { "Построение аккорда", ExerciseType::ChordBuild},
                                  }},
            { BlockCategory::Notes, {
                                 { "Название ноты", ExerciseType::NoteBuild},
                                 { "Определение ноты", ExerciseType::NoteRecognise},
                                 { "Определение нот в мелодии",   ExerciseType::NoteGuess},
                                 }},
            { BlockCategory::Rhythm, {
                                  { "Определение ритма", ExerciseType::RhythmRecognise},
                                  }},
            { BlockCategory::Melody, {
                                     { "Повтор мелодии", ExerciseType::MelodyRepeat},
                                    {"Определение направления мелодии", ExerciseType::MelodyDirection}
                                     }},
            };
    return configs;
}

void StartWidget::setBlock(int block) {
    BlockCategory category = static_cast<BlockCategory>(block);
    clearButtons();
    const auto& entries = blockConfigs().value(static_cast<BlockCategory>(block));
    for (const auto& entry : entries) {
        addButton(entry.title, entry.type);
    }
}

void StartWidget::clearButtons() {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}
