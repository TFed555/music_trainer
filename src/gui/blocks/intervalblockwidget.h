#ifndef INTERVALBLOCKWIDGET_H
#define INTERVALBLOCKWIDGET_H

#include <QWidget>

namespace Ui {
class IntervalBlockWidget;
}

class IntervalBlockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IntervalBlockWidget(QWidget *parent = nullptr);
    ~IntervalBlockWidget();
signals:
    void backClicked();
    void exerciseSelected(int exerciseId);
private:
    Ui::IntervalBlockWidget *ui;
};

#endif // INTERVALBLOCKWIDGET_H
