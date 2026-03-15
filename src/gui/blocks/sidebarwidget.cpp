#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

SidebarWidget::SidebarWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SidebarWidget)
{
    ui->setupUi(this);
    anim = new QPropertyAnimation(this, "maximumWidth");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(addNavButton("Интервалы", StartWidget::BlockCategory::Intervals));
    layout->addWidget(addNavButton("Аккорды", StartWidget::BlockCategory::Chords));
    layout->addWidget(addNavButton("Ноты", StartWidget::BlockCategory::Notes));
}

SidebarWidget::~SidebarWidget()
{
    delete ui;
}

QPushButton* SidebarWidget::addNavButton(const QString& title, StartWidget::BlockCategory block) {
    QPushButton* btn = new QPushButton(title);
    btn->setFlat(true);
    connect(btn, &QPushButton::clicked, this, [this, block](){
        emit blockSelected(block);
    });
    return btn;
}

void SidebarWidget::open() {
    anim->setStartValue(isOpen ? 200 : 0);
    anim->setEndValue(isOpen ? 0 : 200);
    anim->start();
    isOpen = !isOpen;
}
