#include "notetileswidget.h"
#include "ui_notetileswidget.h"
#include "../../music/pitchutils.h"


NoteTilesWidget::NoteTilesWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NoteTilesWidget)
{
    ui->setupUi(this);
    setNotes();
}

NoteTilesWidget::~NoteTilesWidget()
{
    delete ui;
}

void NoteTilesWidget::setNotes() {
    notes.resize(13);
    for (int i = 0; i < notes.size(); i++) {
        notes[i].name = MusicTheory::noteNames[i];
    }
}

void NoteTilesWidget::paintEvent(QPaintEvent* event) {
    if (notes.empty()) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int tileWidth = width() / notes.size();
    int tileHeight = height();

    for (int i = 0; i < notes.size(); i++) {
        QRect rect(i*tileWidth, 0, tileWidth, tileHeight);
        if (mode == Mode::Input && i == selectedIndex) {
            painter.setBrush(QColor("#66ccff"));
        }
        else if (mode == Mode::Result && highlightedIndexes.contains(i)) {
            painter.setBrush(QColor("#008000")); //зеленый
        }
        else {
            painter.setBrush(QColor("#dddddd"));
        }

        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, notes[i].name);
    }
}

void NoteTilesWidget::mousePressEvent(QMouseEvent* event) {
    if (notes.empty()) return;
    if (mode != Mode::Input)
        return;

    int tileWidth = width() / notes.size();
    int index = event->pos().x() / tileWidth;
    if (index >= 0 && index < notes.size()) {
        selectedIndex = index;
        emit noteSelected(index, notes[index].name);
        update();
    }
}

void NoteTilesWidget::highlight(const QVector<QString>& noteNames) {
    selectedIndex = -1;
    highlightedIndexes.clear();
    for (int i = 0; i < notes.size(); i++) {
        if (noteNames.contains(notes[i].name)) {
            highlightedIndexes.insert(i);
        }
    }
    update();
}

void NoteTilesWidget::setMode(Mode m) {
    mode = m;
    update();
}
