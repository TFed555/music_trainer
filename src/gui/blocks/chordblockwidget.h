#ifndef CHORDBLOCKWIDGET_H
#define CHORDBLOCKWIDGET_H

#include "IBlockWidget.h"

namespace Ui {
class ChordBlockWidget;
}

class ChordBlockWidget : public IBlockWidget
{
    Q_OBJECT

public:
    explicit ChordBlockWidget(QWidget *parent = nullptr);
    ~ChordBlockWidget();

private:
    Ui::ChordBlockWidget *ui;
};

#endif // CHORDBLOCKWIDGET_H
