#include "notetileswidget.h"
#include "ui_notetileswidget.h"
#include "../../music/pitchutils.h"

NoteTilesWidget::NoteTilesWidget(bool noteNamesVisible, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NoteTilesWidget)
    , noteNamesVisible(noteNamesVisible)
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
    tileCoords.clear();
    if (notes.empty()) return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const QVector<int> blackTiles = {1,3,6,8,10};
    const int whiteCount = notes.size() - blackTiles.size();
    const int tileWidth = width() / whiteCount;
    const int tileHeight = height();
    int whiteIdx = 0;

    for (int i = 0; i < notes.size(); i++) {
        if (blackTiles.contains(i)) continue;
        QRect rect = QRect(whiteIdx*tileWidth, 0, tileWidth, tileHeight);
        tileCoords.append({rect,i,TileType::White});
        whiteIdx++;
        QColor color = setColor(i, TileType::White);

        painter.setBrush(color);
        painter.drawRect(rect);
        if (noteNamesVisible) {
            painter.drawText(rect, Qt::AlignBottom | Qt::AlignCenter, notes[i].name);
        }
    }
    whiteIdx=0;
    for (int i = 0; i < notes.size(); i++) {
        if (!blackTiles.contains(i)) {
            whiteIdx++;
            continue;
        }
        int idx = whiteIdx*tileWidth-tileWidth/2;
        QRect rect = QRect(idx, 0, tileWidth*0.7, tileHeight * 0.7);
        tileCoords.append({rect,i,TileType::Black});
        QColor color = setColor(i, TileType::Black);

        painter.setBrush(color);
        painter.drawRect(rect);
        painter.setPen(QColor(255, 255, 255));
        if (noteNamesVisible) {
            painter.drawText(rect, Qt::AlignBottom | Qt::AlignCenter, notes[i].name);
        }
    }
}

QColor NoteTilesWidget::setColor(int i, TileType type){
    if (mode == Mode::Input && i == selectedIndex) {
        return QColor(124, 206, 247);
    }
    else if (mode == Mode::Question && highlightedIndexes.contains(i)) {
        return QColor(51, 131, 196);
    }
    else if (mode == Mode::Result && wrongIndexes.contains(i)) {
        return QColor(201, 71, 64); //красный
    }
    else if (mode == Mode::Result && highlightedIndexes.contains(i)) {
        return QColor(0, 128, 0); //зеленый
    }
    return type==TileType::White ? QColor(255,255,255) : QColor(10,10,10);
}

void NoteTilesWidget::mousePressEvent(QMouseEvent* event) {
    if (notes.empty()) return;
    if (mode != Mode::Input)
        return;
    QPoint pos = event->pos();

    for (auto t : tileCoords) {
        if (t.rect.contains(pos) && t.type==TileType::Black) {
            selectedIndex = t.noteIdx;
            emit noteSelected(notes[t.noteIdx].name);
            update();
            return;
        }
    }

    for (auto t : tileCoords) {
        if (t.rect.contains(pos) && t.type==TileType::White) {
            selectedIndex = t.noteIdx;
            emit noteSelected(notes[t.noteIdx].name);
            update();
            return;
        }
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

void NoteTilesWidget::resetSelection() {
    selectedIndex = -1;
    update();
}
