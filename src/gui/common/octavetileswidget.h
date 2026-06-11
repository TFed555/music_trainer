#ifndef OCTAVETILESWIDGET_H
#define OCTAVETILESWIDGET_H

#include <QWidget>
#include "notetileswidget.h"
#include <QPushButton>

namespace Ui {
class OctaveTilesWidget;
}

class OctaveTilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OctaveTilesWidget(bool noteNamesVisible = true, QWidget *parent = nullptr);
    ~OctaveTilesWidget();

    void setVisibleOctaves(int count);
    void setSelectedNote(const QString& note);
public slots:
    void highlight(const QVector<QString>& noteNames, const QVector<QString>& selected);
    void setMode(Mode m);
    void resetTiles();
signals:
    void noteSelected(const QString&, const bool);
    void octaveCountChanged(int firstOctave, int lastOctave);
private:
    void resetSelection(int octIdx);
    QPushButton* btnMinus;
    QPushButton* btnPlus;
    int visibleCount;
    QVector<NoteTilesWidget*> octaves;
    static constexpr int octaveCount = 3;
    static constexpr int octaveOffset = 3;
};

#endif // OCTAVETILESWIDGET_H
