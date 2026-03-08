#ifndef NOTETILESWIDGET_H
#define NOTETILESWIDGET_H

#include "../../core/common/models/Note.h"
#include "../../core/common/models/Mode.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class NoteTilesWidget;
}

class NoteTilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoteTilesWidget(QWidget *parent = nullptr);
    ~NoteTilesWidget();

    void highlight(const QVector<QString>& noteNames, const QVector<QString>& selected);
    void setMode(Mode m);
    void resetTiles();
    void resetSelection();
private:
    enum class TileType {
        White,
        Black
    };
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
private:
    void setNotes();
    QColor setColor(int, TileType);
signals:
    void noteSelected(const QString& noteName);

private:
    Ui::NoteTilesWidget *ui;
    int selectedIndex = -1;
    QSet<int> highlightedIndexes;
    QSet<int> wrongIndexes;
    Mode mode = Mode::Input;
    QVector<Note> notes;

};

#endif // NOTETILESWIDGET_H
