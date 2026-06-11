#include "octavetileswidget.h"
#include <QHBoxLayout>

OctaveTilesWidget::OctaveTilesWidget(bool noteNamesVisible, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    btnMinus = new QPushButton("-", this);
    btnPlus = new QPushButton("+", this);

    for (auto* btn : {btnMinus, btnPlus}) {
        btn->setFixedSize(28, 28);
        btn->setObjectName("octBtn");
    }

    layout->addWidget(btnMinus, 0, Qt::AlignVCenter);

    for (int i = 0; i < octaveCount; i++) {
        NoteTilesWidget* tiles = new NoteTilesWidget(noteNamesVisible, this);
        tiles->show();
        tiles->setFixedWidth(parent->width()/octaveCount);
        layout->addWidget(tiles, 1);
        connect(tiles, &NoteTilesWidget::noteSelected,
                this, [this, i] (QString noteName, bool listenOnly) {
            QString note = QString("%1 %2").arg(noteName).arg(QString::number(i+octaveOffset));
            emit noteSelected(note, listenOnly);
            resetSelection(i);
        });
        octaves.append(tiles);
    }

    layout->addWidget(btnPlus, 0, Qt::AlignVCenter);
    connect(btnMinus, &QPushButton::clicked, this, [this]() {
        setVisibleOctaves(visibleCount - 1);
    });
    connect(btnPlus, &QPushButton::clicked, this, [this]() {
        setVisibleOctaves(visibleCount + 1);
    });
    setVisibleOctaves(3);
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
        qDebug() << list;
        int oct = list[1].toInt();
        selectedByOctave[oct].append(list[0]);
    }

    for (int i = 0; i < octaves.size(); i++) {
        octaves[i]->highlight(groupByOctave[i+3], selectedByOctave[i+3]);
        qDebug() << "octave" << i+3;
    }
}

void OctaveTilesWidget::setSelectedNote(const QString& note) {
    auto list = note.split(" ");
    int oct = list[1].toInt() - 3;
    qDebug() << oct;
    if (oct > octaves.size()) return;
    octaves[oct]->setSelectedNote(list[0]);
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
    visibleCount = count;
    int firstIdx = (count == 1) ? 1 : 0;
    for (int i = 0; i < octaves.size(); i++) {
        octaves[i]->setVisible(i>=firstIdx && i<firstIdx+count);
    }
    btnMinus->setEnabled(count > 1);
    btnPlus->setEnabled(count < 3);
    int firstOctave = count == 1 ? firstIdx : 0;
    int lastOctave = firstOctave + count - 1;
    emit octaveCountChanged(firstOctave, lastOctave);
}
