#ifndef NOTETILESWIDGET_H
#define NOTETILESWIDGET_H

#include "../audio/playback/noteplayer.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

struct Note {
    QString name;
    int midi;
};

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
    void noteSelected(int index, const QString& noteName);
private:
    Ui::NoteTilesWidget *ui;
    QVector<Note> notes;
    int selectedIndex = -1;
    QSet<int> highlightedIndexes;
    Mode mode = Mode::Input;
    AudioProcessor* processor;
    NotePlayer notePlayer;
};

#endif // NOTETILESWIDGET_H
