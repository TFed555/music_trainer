#include "rhythmcanvaswidget.h"

RhythmCanvasWidget::RhythmCanvasWidget(QWidget *parent)
    : QWidget(parent)
{
}

RhythmCanvasWidget::~RhythmCanvasWidget()
{
}

void RhythmCanvasWidget::paintEvent(QPaintEvent* event) {
    using namespace MusicUtils::Rhythm;
    QPainter painter(this);
    QFont musicFont("Bravura", 40);
    painter.setFont(musicFont);
    qDebug() << painter.font().family();
    QRect rect;
    int x = 10;
    for (auto n : rhythmNotes) {
        rect = QRect(x, 0, 100, 100);
        painter.drawText(rect, Qt::AlignLeft|Qt::AlignVCenter,
                         QString(musicSymbol[n]));
        x+=70;
    }
}

void RhythmCanvasWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        qDebug() << "key pressed";
        emit
    }
}
