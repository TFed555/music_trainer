#include "exercisewithtileswidget.h"
#include "ui_exercisewithtileswidget.h"
#include <QTimer>

ExerciseWithTilesWidget::ExerciseWithTilesWidget(bool noteNamesVisible, QWidget *parent)
    : IExerciseWidget(parent)
    , ui(new Ui::ExerciseWithTilesWidget)
    , tiles(new OctaveTilesWidget(noteNamesVisible, this))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(tiles);
    tiles->setFixedWidth(700);

    connect(ui->startBtn, &QPushButton::clicked, this, [this] {
            emit startClicked();
            setMode(Mode::Wait);
        });
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::backClicked);
    connect(tiles, &OctaveTilesWidget::noteSelected, this, &ExerciseWithTilesWidget::noteSelected);
    connect(this, &ExerciseWithTilesWidget::resetTiles, tiles, &OctaveTilesWidget::resetTiles);
    // connect(ui->difficultyBox, &QComboBox::activated,
    //         this, &ExerciseWithTilesWidget::difficultyChanged);
    connect(ui->difficultyBox, &QComboBox::currentIndexChanged,
            this, &ExerciseWithTilesWidget::difficultyChanged);
}

ExerciseWithTilesWidget::~ExerciseWithTilesWidget()
{
    delete ui;
}

void ExerciseWithTilesWidget::exercisePlayFinished() {
    setMode(Mode::Input);
}

void ExerciseWithTilesWidget::showResult(const QVector<QString>& correct, const QVector<QString>& selected) {
    tiles->highlight(correct, selected);
    QTimer::singleShot(2000, this, [this]() {
        setMode(Mode::Input);
        emit resetTiles();
    });
}

void ExerciseWithTilesWidget::setMode(Mode m) {
    tiles->setMode(m);
}

void ExerciseWithTilesWidget::setQuestion(const QString& question) {
    if (questionLabel) {
        delete questionLabel;
        questionLabel = nullptr;
    }
    questionLabel = new QLabel(question, this);
    ui->manageLayout->addWidget(questionLabel);
}

void ExerciseWithTilesWidget::highlightQuestion(QVector<QString> notes) {
    tiles->highlight(notes, {});
}

void ExerciseWithTilesWidget::setOctaveCount(int count) {
    tiles->setVisibleOctaves(count);
}
