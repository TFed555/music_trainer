#include "startwidget.h"
#include <QPushButton>
#include <QEvent>
#include <QFrame>
#include <QLabel>
#include "../../core/common/models/exercisestrings.h"

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    rootLayout = new QVBoxLayout(this);
    rootLayout->setAlignment(Qt::AlignCenter);
    rootLayout->setSpacing(12);
    rootLayout->setContentsMargins(20, 20, 20, 20);
    currentBlock = 0;
    setBlock(0);
}

StartWidget::~StartWidget()
{
}

void StartWidget::addButton(const QString& title, ExerciseType type) {
    QPushButton* btn = new QPushButton();
    btn->setText(title);
    btn->setMinimumHeight(44);
    btn->setMaximumWidth(320);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btn->setObjectName("exerciseBtn");

    connect(btn, &QPushButton::clicked, this, [this, type](){
        emit exerciseSelected(type);
    });
}

void StartWidget::setBlock(int block) {
    clearButtons();

    QFrame* card = new QFrame();
    card->setMaximumWidth(700);
    card->setMaximumHeight(800);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setSpacing(10);
    BlockCategory category = static_cast<BlockCategory>(block);

    QLabel* title = new QLabel(ExerciseStrings::blockName(category));
    title->setObjectName("blockLabel");
    cardLayout->addWidget(title);

    QGridLayout* grid = new QGridLayout();
    grid->setSpacing(10);
    cardLayout->addLayout(grid);

    int row = 0, col = 0;

    for (const auto& type : ExerciseStrings::blockConfigs[category].exercises) {
        QPushButton* btn = new QPushButton(ExerciseStrings::displayName(type));
        btn->setMinimumHeight(44);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btn->setObjectName("exerciseBtn");

        connect(btn, &QPushButton::clicked, this, [this, type]() {
            emit exerciseSelected(type);
        });

        grid->addWidget(btn, row, col);

        col++;
        if (col == 2) {
            col = 0;
            row++;
        }
    }

    rootLayout->addWidget(card, 0, Qt::AlignHCenter);

    currentBlock = block;
}

void StartWidget::clearButtons() {
    QLayoutItem* item;
    while ((item = rootLayout->takeAt(0)) != nullptr) {
        if (item->widget())
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
