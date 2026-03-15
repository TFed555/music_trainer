#ifndef NOTEBLOCKWIDGET_H
#define NOTEBLOCKWIDGET_H

#include "IBlockWidget.h"

namespace Ui {
class NoteBlockWidget;
}

class NoteBlockWidget : public IBlockWidget
{
    Q_OBJECT

public:
    explicit NoteBlockWidget(QWidget *parent = nullptr);
    ~NoteBlockWidget();

private:
    Ui::NoteBlockWidget *ui;
};

#endif // NOTEBLOCKWIDGET_H
