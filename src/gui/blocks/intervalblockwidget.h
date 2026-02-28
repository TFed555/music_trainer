#ifndef INTERVALBLOCKWIDGET_H
#define INTERVALBLOCKWIDGET_H

#include "IBlockWidget.h"

namespace Ui {
class IntervalBlockWidget;
}

class IntervalBlockWidget : public IBlockWidget
{
    Q_OBJECT

public:
    explicit IntervalBlockWidget(QWidget *parent = nullptr);
    ~IntervalBlockWidget();
private:
    Ui::IntervalBlockWidget *ui;
};

#endif // INTERVALBLOCKWIDGET_H
