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
    ui->modeLabel->setText("");
    tiles->setFixedWidth(700);

    connect(ui->startBtn, &QPushButton::clicked, this, [this] {
            emit startClicked();
            setMode(Mode::Wait);
        });
    connect(ui->stopBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::stopClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::backClicked);
    connect(ui->replayBtn, &QPushButton::clicked, this, &ExerciseWithTilesWidget::replayClicked);
    ui->replayBtn->setEnabled(false);
    connect(tiles, &OctaveTilesWidget::noteSelected, this, &ExerciseWithTilesWidget::noteSelected);
    connect(this, &ExerciseWithTilesWidget::resetTiles, tiles, &OctaveTilesWidget::resetTiles);
    connect(ui->difficultyBox, &QComboBox::currentIndexChanged,
            this, &ExerciseWithTilesWidget::difficultyChanged);
    connect(ui->modeBox, &QComboBox::currentIndexChanged,
            this, [this](int m) {
        Mode mode = static_cast<Mode>(m);
        setMode(mode);
    });
}

ExerciseWithTilesWidget::~ExerciseWithTilesWidget()
{
    delete ui;
}

void ExerciseWithTilesWidget::exercisePlayFinished() {
    ui->difficultyBox->setEnabled(false);
    int m = ui->modeBox->currentIndex();
    switch(m){
    case 0:
        setMode(Mode::Try);
        break;
    case 1:
        setMode(Mode::Input);
        break;
    }
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
    switch (m) {
        case Mode::Wait:
            ui->modeLabel->setText("Слушайте");
            break;
        case Mode::Input:
            ui->modeLabel->setText("Введите ответ");
            break;
        case Mode::Result:
            ui->modeLabel->setText("");
            break;
        case Mode::Question:
            ui->modeLabel->setText("");
            break;
        case Mode::Try:
            ui->modeLabel->setText("");
            break;
    }
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

void ExerciseWithTilesWidget::setDescription(const QString& text) {
    ui->descriptionLabel->setText(text);
}

void ExerciseWithTilesWidget::onReplayAvailable(int replays) {
    bool en = replays <= 0 ? false : true;
    ui->replayBtn->setEnabled(en);
}
