#include "sidebarwidget.h"
#include <QEvent>
#include <QStyle>

SidebarWidget::SidebarWidget(QWidget *parent)
    : QWidget(parent)
{
    rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(8, 16, 8, 16);
    rootLayout->setSpacing(20);
    setLayout();
    anim = new QPropertyAnimation(this, "maximumWidth");
}

SidebarWidget::~SidebarWidget()
{
}

void SidebarWidget::setLayout() {
    clearButtons();

    for (const auto& block : ExerciseStrings::blockConfigs.keys()) {
        auto btn = addNavButton(ExerciseStrings::blockName(block), block);
        rootLayout->addWidget(btn);
        if (block == BlockCategory::Intervals) {
            activeBtn = btn;
        }
    }
    rootLayout->addStretch();
}

QPushButton* SidebarWidget::addNavButton(const QString& title, BlockCategory block) {
    QPushButton* btn = new QPushButton(title);
    btn->setObjectName("blockBtn");
    connect(btn, &QPushButton::clicked, this, [this, btn, block](){
        if (activeBtn) {
            activeBtn->setProperty("active", false);
            activeBtn->style()->unpolish(activeBtn);
            activeBtn->style()->polish(activeBtn);
        }

        btn->setProperty("active", true);
        btn->style()->unpolish(btn);
        btn->style()->polish(btn);
        activeBtn = btn;
        emit blockSelected(static_cast<int>(block));
    });
    return btn;
}

void SidebarWidget::toggle() {
    anim->setStartValue(isOpen ? 200 : 0);
    anim->setEndValue(isOpen ? 0 : 200);
    anim->start();
    isOpen = !isOpen;
}

void SidebarWidget::close() {
    if (isOpen) {
        toggle();
    }
}

void SidebarWidget::clearButtons() {
    QLayoutItem* item;
    while ((item = rootLayout->takeAt(0)) != nullptr) {
        if (item->widget())
            delete item->widget();
        delete item;
    }
}

void SidebarWidget::changeEvent(QEvent* event) {
    if (event->type() == QEvent::LanguageChange) {
        setLayout();
    }
    QWidget::changeEvent(event);
}

void SidebarWidget::retranslate() {
    // intervalsBtn->setText(tr("Интервалы"));
    // chordsBtn->setText(tr("Аккорды"));
    // notesBtn->setText(tr("Ноты"));
    // rhythmBtn->setText(tr("Ритм"));
    // melodyBtn->setText(tr("Мелодический слух"));
}
