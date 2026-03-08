#include "octavetileswidget.h"
// #include "ui_octavetileswidget.h"
#include <QHBoxLayout>

OctaveTilesWidget::OctaveTilesWidget(QWidget *parent)
    : QWidget(parent)
    // , ui(new Ui::OctaveTilesWidget)
{
    // ui->setupUi(this);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    for (size_t i = 0; i < 3; i++) {
        NoteTilesWidget* tiles = new NoteTilesWidget(this);
        tiles->show();
        layout->addWidget(tiles);
        connect(tiles, &NoteTilesWidget::noteSelected,
                this, [this, i] (QString noteName) {
            emit noteSelected(QString("%1 %2").arg(noteName).arg(QString::number(i+3)));
            resetSelection(i);
        });
        octaves.append(tiles);
    }
}

OctaveTilesWidget::~OctaveTilesWidget()
{
    // delete ui;
}

void OctaveTilesWidget::resetSelection(int octIdx) {
    for (size_t i = 0; i < octaves.size(); i++) {
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
