#ifndef RHYTHMCANVASWIDGET_H
#define RHYTHMCANVASWIDGET_H

#include <QObject>
#include <QWidget>
#include "../../music/pitchutils.h"
#include <QKeyEvent>
#include <QPainter>
#include "../../core/common/models/Mode.h"
#include <QTimer>

class RhythmCanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RhythmCanvasWidget(QWidget *parent = nullptr);
    ~RhythmCanvasWidget();
    void setNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes, int bpm);

    const QMap<MusicUtils::Rhythm::RhythmType, QChar> musicSymbol {
        {MusicUtils::Rhythm::RhythmType::Whole, QChar(0xE0A2)},
        {MusicUtils::Rhythm::RhythmType::Half, QChar(0xECA3)},
        {MusicUtils::Rhythm::RhythmType::Quarter, QChar(0xECA5)},
        {MusicUtils::Rhythm::RhythmType::Eighth, QChar(0xECA7)},
        {MusicUtils::Rhythm::RhythmType::Sixteenth, QChar(0xECA9)}
    };

public slots:
    void exerciseStarted();
protected:
    void paintEvent(QPaintEvent* event) override;
    // void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    float durationMs(MusicUtils::Rhythm::RhythmType type);
signals:
    void inputFinished(const QVector<int>& notePoses, const QVector<int>& userTaps);
private:
    QVector<MusicUtils::Rhythm::RhythmType> rhythmNotes;
    float currentBeatX = 0.0f;
    float currentUserX = 0.0f;
    QVector<int> userTaps;
    Mode mode = Mode::Wait;
    QTimer* beatTimer = nullptr;
    QTimer* userTimer = nullptr;
    QVector<int> notePoses;
    float pxPerMs = 0.1f;
    int bpm;
    int startX = 0;
    float beatStep;
    float userStep;
    float msPerBeat;
    float durationMin;
};

#endif // RHYTHMCANVASWIDGET_H
