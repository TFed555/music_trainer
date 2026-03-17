#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

SidebarWidget::SidebarWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SidebarWidget)
{
    ui->setupUi(this);
    setLayout();
    anim = new QPropertyAnimation(this, "maximumWidth");
}

SidebarWidget::~SidebarWidget()
{
    delete ui;
}

void SidebarWidget::setLayout() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(20);
    layout->addWidget(addNavButton("Интервалы", StartWidget::BlockCategory::Intervals));
    layout->addWidget(addNavButton("Аккорды", StartWidget::BlockCategory::Chords));
    layout->addWidget(addNavButton("Ноты", StartWidget::BlockCategory::Notes));
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

void SidebarWidget::open() {
    anim->setStartValue(isOpen ? 200 : 0);
    anim->setEndValue(isOpen ? 0 : 200);
    anim->start();
    isOpen = !isOpen;
}
