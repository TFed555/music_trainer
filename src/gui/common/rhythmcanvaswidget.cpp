#include "rhythmcanvaswidget.h"
using namespace MusicUtils::Rhythm;
RhythmCanvasWidget::RhythmCanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

RhythmCanvasWidget::~RhythmCanvasWidget()
{
}

float RhythmCanvasWidget::durationMs(MusicUtils::Rhythm::RhythmType type) {
    float msPerBeat = 60000.0f/bpm;
    switch(type) {
    case RhythmType::Whole:    return msPerBeat * 4;
    case RhythmType::Half:     return msPerBeat * 2;
    case RhythmType::Quarter:  return msPerBeat * 1;
    case RhythmType::Eighth:   return msPerBeat * 0.5f;
    case RhythmType::Sixteenth: return msPerBeat * 0.25f;
    }
}

void RhythmCanvasWidget::setNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes, int r_bpm) {
    rhythmNotes = notes;
    bpm = r_bpm;
    notePoses.clear();
    int x = startX;
    float total = 0;
    for (auto n : notes) total += durationMs(n);
    pxPerMs = (width()-x*2) / total;
    step = pxPerMs * 16.0f;
    for (auto n : notes) {
        notePoses.append(x);
        x+=durationMs(n) * pxPerMs;
    }
    update();
}

void RhythmCanvasWidget::paintEvent(QPaintEvent* event) {
    using namespace MusicUtils::Rhythm;
    QPainter painter(this);
    QFont musicFont("Bravura", 40);
    painter.setFont(musicFont);
    // qDebug() << painter.font().family();
    QRect rect;
    int y = height() * 0.75;
    for (int i = 0; i < rhythmNotes.size(); i++) {
        rect = QRect(notePoses[i], 10, 100, 100);
        painter.drawText(rect, Qt::AlignLeft|Qt::AlignVCenter,
                         QString(musicSymbol[rhythmNotes[i]]));
    }
    if (mode == Mode::Input) {
        painter.drawLine(0, y, width(), y);
        painter.setPen(Qt::black);
        painter.drawLine((int)currentBeatX, y-10, (int)currentBeatX, y+10);
        painter.setPen(Qt::red);
        for (int tapX : userTaps) {
            painter.drawEllipse(tapX - 4, y - 4, 15, 15);
        }
    }
}

void RhythmCanvasWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        qDebug() << "key pressed";
        userTaps.append(currentBeatX);
        update();
        // emit

    }
}

void RhythmCanvasWidget::exerciseStarted() {
    qDebug() << "bpm:" << bpm;
    qDebug() << "pxPerMs:" << pxPerMs;
    qDebug() << "step:" << step;
    qDebug() << "quarter px:" << durationMs(MusicUtils::Rhythm::RhythmType::Quarter) * pxPerMs;
    qDebug() << "total time ms:" << [this]() {
        float t = 0;
        for (auto n : rhythmNotes) t += durationMs(n);
        return t;
    }();
    currentBeatX = 0.0f;
    userTaps.clear();
    mode = Mode::Input;
    if (!timer) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            currentBeatX += durationMs(RhythmType::Quarter) * pxPerMs;
            if (currentBeatX > width()) {
                timer->stop();
                mode = Mode::Result;
            }
            update();
        });
    }
    QTimer::singleShot(1000, this, [this]() {
        timer->start(60000/bpm);
    });
}
