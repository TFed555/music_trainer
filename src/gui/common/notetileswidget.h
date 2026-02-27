#ifndef NOTETILESWIDGET_H
#define NOTETILESWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "../core/controllers/tilescontroller.h"


namespace Ui {
class NoteTilesWidget;
}

class NoteTilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoteTilesWidget(QWidget *parent = nullptr);
    ~NoteTilesWidget();
    enum class Mode {
        Input,
        Result
    };

    void highlight(const QVector<QString>& noteNames);
    void setMode(Mode m);

protected:
    void paintEvent(QPaintEvent* event) override;
    void setNotes();
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void noteSelected(const QString& noteName);
private:
    Ui::NoteTilesWidget *ui;
    TilesController* controller;
    int selectedIndex = -1;
    QSet<int> highlightedIndexes;
    Mode mode = Mode::Input;
    QVector<Note> notes;
};

#endif // NOTETILESWIDGET_H
