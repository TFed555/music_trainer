#ifndef RHYTHMCANVASWIDGET_H
#define RHYTHMCANVASWIDGET_H

#include <QObject>
#include <QWidget>
#include "../../music/pitchutils.h"
#include <QKeyEvent>
#include <QPainter>

class RhythmCanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RhythmCanvasWidget(QWidget *parent = nullptr);
    ~RhythmCanvasWidget();
    void setNotes(const QVector<MusicUtils::Rhythm::RhythmType>& notes) {
        rhythmNotes = notes;
        update();
    }
    const QMap<MusicUtils::Rhythm::RhythmType, QChar> musicSymbol {
        {MusicUtils::Rhythm::RhythmType::Whole, QChar(0xE0A2)},
        {MusicUtils::Rhythm::RhythmType::Half, QChar(0xECA3)},
        {MusicUtils::Rhythm::RhythmType::Quarter, QChar(0xECA5)},
        {MusicUtils::Rhythm::RhythmType::Eighth, QChar(0xECA7)},
        {MusicUtils::Rhythm::RhythmType::Sixteenth, QChar(0xECA9)}
    };
protected:
    void paintEvent(QPaintEvent* event) override;
    // void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    QVector<MusicUtils::Rhythm::RhythmType> rhythmNotes;
};

#endif // RHYTHMCANVASWIDGET_H
