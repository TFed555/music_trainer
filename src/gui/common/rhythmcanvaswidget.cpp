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
    msPerBeat = 60000.0f/r_bpm;
    int realBpm = 60000.0f/r_bpm;
    int x = startX;
    float total = 0;
    durationMin = durationMs(MusicUtils::Rhythm::RhythmType::Quarter);
    for (auto n : notes){
        float d = durationMs(n);
        total += d;
        durationMin = qMin(durationMin, d);
    }
    pxPerMs = (width()-x*2) / total;
    beatStep = pxPerMs * durationMin;
    userStep = pxPerMs * durationMs(MusicUtils::Rhythm::RhythmType::Sixteenth);
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
        painter.setPen(Qt::blue);
        painter.drawLine((int)currentUserX, y-10, (int)currentUserX, y+10);
        painter.setPen(Qt::red);
        for (int tapX : userTaps) {
            painter.drawEllipse(tapX - 4, y - 4, 15, 15);
        }
    }
}

void RhythmCanvasWidget::handleTap() {
    qDebug() << "key pressed";
    userTaps.append(currentUserX);
    update();
}

void RhythmCanvasWidget::exerciseStarted() {
    if (beatTimer) beatTimer->stop();
    if (userTimer) userTimer->stop();
    qDebug() << "bpm:" << bpm;
    qDebug() << "userstep:" << userStep;
    qDebug() << "step:" << beatStep;
    float beatTickMs = durationMin;
    float userTickMs = durationMs(MusicUtils::Rhythm::RhythmType::Sixteenth);
    currentBeatX = 0.0f;
    currentUserX = 0.0f;
    userTaps.clear();
    mode = Mode::Input;
    if (!beatTimer) {
        beatTimer = new QTimer(this);
        connect(beatTimer, &QTimer::timeout, this, [this]() {
            currentBeatX += beatStep;
            if (currentBeatX > width()) {
                beatTimer->stop();
                mode = Mode::Result;
                emit inputFinished(notePoses, userTaps);
            }
            update();
        });
    }

    if (!userTimer) {
        userTimer = new QTimer(this);
        connect(userTimer, &QTimer::timeout, this, [this]() {
            currentUserX += userStep;
            if (currentUserX > width()) {
                userTimer->stop();
            }
            update();
        });
    }

    QTimer::singleShot(1000, this, [this, beatTickMs, userTickMs]() {
        beatTimer->start(static_cast<int>(beatTickMs));
        userTimer->start(static_cast<int>(userTickMs));
        update();
    });
}
