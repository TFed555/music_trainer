#include "octavetileswidget.h"
#include <QHBoxLayout>

OctaveTilesWidget::OctaveTilesWidget(bool noteNamesVisible, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    for (int i = 0; i < octaveCount; i++) {
        NoteTilesWidget* tiles = new NoteTilesWidget(noteNamesVisible, this);
        tiles->show();
        tiles->setFixedWidth(parent->width()/octaveCount);
        layout->addWidget(tiles);
        connect(tiles, &NoteTilesWidget::noteSelected,
                this, [this, i] (QString noteName) {
            QString note = QString("%1 %2").arg(noteName).arg(QString::number(i+octaveOffset));
            emit noteSelected(note);
            resetSelection(i);
        });
        octaves.append(tiles);
    }
}

OctaveTilesWidget::~OctaveTilesWidget() {}

void OctaveTilesWidget::resetSelection(int octIdx) {
    for (int i = 0; i < octaves.size(); i++) {
        if (i != octIdx){
            octaves[i]->resetSelection();
        }
    }
}

void OctaveTilesWidget::highlight(const QVector<QString>& noteNames, const QVector<QString>& selected) {
    QMap<int, QVector<QString>> groupByOctave;
    QMap<int, QVector<QString>> selectedByOctave;
    qDebug() << "noteNames " << noteNames;
    qDebug() << "selected " << selected;
    for (const QString& name : noteNames) {
        auto list = name.split(" ");
        int oct = list[1].toInt();
        groupByOctave[oct].append(list[0]);
    }
    for (const QString& name : selected) {
        auto list = name.split(" ");
        int oct = list[1].toInt();
        selectedByOctave[oct].append(list[0]);
    }

    for (int i = 0; i < octaves.size(); i++) {
        octaves[i]->highlight(groupByOctave[i+3], selectedByOctave[i+3]);
        qDebug() << "octave" << i+3;
    }
}

void OctaveTilesWidget::setMode(Mode m) {
    for (auto* w : octaves) {
        w->setMode(m);
    }
}

void OctaveTilesWidget::resetTiles() {
    for (auto* w : octaves) {
        w->resetTiles();
    }
}

void OctaveTilesWidget::setVisibleOctaves(int count) {
    int firstIdx = (count == 1) ? 1 : 0;
    for (int i = 0; i < octaves.size(); i++) {
        octaves[i]->setVisible(i>=firstIdx && i<firstIdx+count);
    }
}
