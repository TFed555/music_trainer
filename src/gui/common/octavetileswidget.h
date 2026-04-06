#ifndef OCTAVETILESWIDGET_H
#define OCTAVETILESWIDGET_H

#include <QWidget>
#include "notetileswidget.h"

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
public slots:
    void highlight(const QVector<QString>& noteNames, const QVector<QString>& selected);
    void setMode(Mode m);
    void resetTiles();
signals:
    void noteSelected(const QString&);
private:
    void resetSelection(int octIdx);
private:
    QVector<NoteTilesWidget*> octaves;
    static constexpr int octaveCount = 3;
    static constexpr int octaveOffset = 3;
};

#endif // OCTAVETILESWIDGET_H
