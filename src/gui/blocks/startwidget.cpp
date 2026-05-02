#include "startwidget.h"
#include <QPushButton>
#include <QEvent>
#include "../../core/common/models/exercisestrings.h"

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    layout->addStretch();
    currentBlock = 0;
    setBlock(0);
}

StartWidget::~StartWidget()
{
}

const QMap<StartWidget::BlockCategory, StartWidget::BlockConfig>
    StartWidget::blockConfigs = {
        { StartWidget::BlockCategory::Intervals,
            BlockConfig{
                {
                    ExerciseType::IntervalRecognise,
                    ExerciseType::IntervalIdentify,
                    ExerciseType::IntervalBuild,
                    ExerciseType::IntervalDirection
                }
            }
        },
        { StartWidget::BlockCategory::Chords,
            BlockConfig{
                {
                    ExerciseType::ChordBuild,
                    ExerciseType::ChordIdentify,
                    ExerciseType::ChordInversion,
                    ExerciseType::ChordRoot
                }
            }
        },
        { StartWidget::BlockCategory::Notes,
            BlockConfig{
                {
                    ExerciseType::NoteBuild,
                    ExerciseType::NoteGuess
                }
            }
        },
        { StartWidget::BlockCategory::Rhythm,
            BlockConfig{
                {
                    ExerciseType::RhythmRecognise
                }
            }
        },
        { StartWidget::BlockCategory::Melody,
            BlockConfig{
                {
                    ExerciseType::MelodyDirection,
                    ExerciseType::MelodyRepeat
                }
            }
        }
};

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
    for (const auto& type : blockConfigs[category].exercises) {
        QString text = ExerciseStrings::displayName(type);
        addButton(text, type);
    }
    currentBlock = block;
}

void StartWidget::clearButtons() {
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void StartWidget::changeEvent(QEvent* event) {
    if (event->type() == QEvent::LanguageChange) {
        setBlock(currentBlock);
    }
    QWidget::changeEvent(event);
}
