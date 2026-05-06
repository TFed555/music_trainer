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
    ui->tipLabel->setText("");
    tiles->setFixedWidth(700);
    ui->startBtn->setObjectName("startBtn");
    ui->backBtn->setObjectName("backBtn");
    ui->replayBtn->setObjectName("replayBtn");

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
    ui->difficultyBox->setEnabled(true);
    tiles->highlight(correct, selected);
    QTimer::singleShot(2000, this, [this]() {
        setMode(Mode::Try);
        emit resetTiles();
    });
}

void ExerciseWithTilesWidget::setMode(Mode m) {
    tiles->setMode(m);
    switch (m) {
        case Mode::Wait:
            ui->tipLabel->setText(tr("Слушайте"));
            break;
        case Mode::Input:
            ui->tipLabel->setText(tr("Введите ответ"));
            break;
        case Mode::Result:
            ui->tipLabel->setText("");
            break;
        case Mode::Question:
            ui->tipLabel->setText("Слушайте");
            break;
        case Mode::Try:
            ui->tipLabel->setText("");
            break;
    }
}

void ExerciseWithTilesWidget::setQuestion(const QString& question) {
    if (questionLabel) {
        delete questionLabel;
        questionLabel = nullptr;
    }
    questionLabel = new QLabel(question, this);
    ui->verticalLayout->addWidget(questionLabel);
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

void ExerciseWithTilesWidget::retranslate() {
    ui->startBtn->setText(tr("Старт"));
    ui->stopBtn->setText(tr("Стоп"));
    ui->replayBtn->setText(tr("Повторить"));
    ui->backBtn->setText(tr("Назад"));
    ui->difficultyLabel->setText(tr("Уровень сложности"));

    int currentDifIndex = ui->difficultyBox->currentIndex();
    ui->difficultyBox->blockSignals(true);
    ui->difficultyBox->clear();
    for (const auto& item : getDifficultyItems()) {
        ui->difficultyBox->addItem(item);
    }
    ui->difficultyBox->setCurrentIndex(currentDifIndex);
    ui->difficultyBox->blockSignals(false);

    ui->modeLabel->setText(tr("Режим"));

    int currentModeIndex = ui->modeBox->currentIndex();
    ui->modeBox->blockSignals(true);
    ui->modeBox->clear();
    for (const auto& item : getModeItems()) {
        ui->modeBox->addItem(item);
    }
    ui->modeBox->setCurrentIndex(currentModeIndex);
    ui->modeBox->blockSignals(false);
    emit langChange();
}
