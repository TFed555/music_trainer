#include "sidebarwidget.h"
#include <QEvent>

SidebarWidget::SidebarWidget(QWidget *parent)
    : QWidget(parent)
{
    setLayout();
    anim = new QPropertyAnimation(this, "maximumWidth");
}

SidebarWidget::~SidebarWidget()
{
}

void SidebarWidget::setLayout() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);
    intervalsBtn = addNavButton(tr("Интервалы"), StartWidget::BlockCategory::Intervals);
    chordsBtn = addNavButton(tr("Аккорды"), StartWidget::BlockCategory::Chords);
    notesBtn = addNavButton(tr("Ноты"), StartWidget::BlockCategory::Notes);
    rhythmBtn = addNavButton(tr("Ритм"), StartWidget::BlockCategory::Rhythm);
    melodyBtn = addNavButton(tr("Мелодический слух"), StartWidget::BlockCategory::Melody);
    layout->addWidget(intervalsBtn);
    layout->addWidget(chordsBtn);
    layout->addWidget(notesBtn);
    layout->addWidget(rhythmBtn);
    layout->addWidget(melodyBtn);
    layout->addStretch();
}

QPushButton* SidebarWidget::addNavButton(const QString& title, StartWidget::BlockCategory block) {
    QPushButton* btn = new QPushButton(title);
    btn->setFlat(true);
    connect(btn, &QPushButton::clicked, this, [this, block](){
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

void SidebarWidget::changeEvent(QEvent* event) {
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }
    QWidget::changeEvent(event);
}

void SidebarWidget::retranslate() {
    intervalsBtn->setText(tr("Интервалы"));
    chordsBtn->setText(tr("Аккорды"));
    notesBtn->setText(tr("Ноты"));
    rhythmBtn->setText(tr("Ритм"));
    melodyBtn->setText(tr("Мелодический слух"));
}
