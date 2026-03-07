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
    explicit OctaveTilesWidget(QWidget *parent = nullptr);
    ~OctaveTilesWidget();

public slots:
    void highlight(const QVector<QString>& noteNames, const QVector<QString>& selected);
    void setMode(Mode m);
    void resetTiles();
signals:
    void noteSelected(const QString);
private:
    void resetSelection(int octIdx);
private:
    Ui::OctaveTilesWidget *ui;
    QVector<NoteTilesWidget*> octaves;
};

#endif // OCTAVETILESWIDGET_H
