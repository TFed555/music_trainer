#include "noteblockwidget.h"
#include "ui_noteblockwidget.h"

NoteBlockWidget::NoteBlockWidget(QWidget *parent)
    : IBlockWidget(parent)
    , ui(new Ui::NoteBlockWidget)
{
    ui->setupUi(this);

    connect(ui->exercise1Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::NoteRecognise, this);
    });
    connect(ui->exercise2Btn, &QPushButton::clicked, this, [this]() {
        emit exerciseSelected(ExerciseType::NoteBuild, this);
    });
    connect(ui->backBtn, &QPushButton::clicked, this, &IBlockWidget::backClicked);
}

NoteBlockWidget::~NoteBlockWidget()
{
    delete ui;
}
