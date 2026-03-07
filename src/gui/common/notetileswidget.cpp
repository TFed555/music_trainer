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
    notes.resize(12);
    for (int i = 0; i < notes.size(); i++) {
        notes[i].name = MusicUtils::noteNames[i];
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
        else if (mode == Mode::Question && highlightedIndexes.contains(i)) {
            painter.setBrush(QColor("#2196F3"));
        }
        else if (mode == Mode::Result && wrongIndexes.contains(i)) {
            painter.setBrush(QColor("#f44336")); //красный
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
        emit noteSelected(notes[index].name);
        update();
    }
}

void NoteTilesWidget::highlight(const QVector<QString>& noteNames, const QVector<QString>& selected) {
    selectedIndex = -1;
    wrongIndexes.clear();
    highlightedIndexes.clear();
    for (int i = 0; i < notes.size(); i++) {
        if (noteNames.contains(notes[i].name)) {
            highlightedIndexes.insert(i);
        }
        if (!selected.isEmpty() && selected.contains(notes[i].name) && !noteNames.contains(notes[i].name)) {
            wrongIndexes.insert(i);
        }
    }
    update();
}

void NoteTilesWidget::setMode(Mode m) {
    mode = m;
    // update();
}

void NoteTilesWidget::resetTiles() {
    wrongIndexes.clear();
    highlightedIndexes.clear();
    selectedIndex = -1;
    update();
}
