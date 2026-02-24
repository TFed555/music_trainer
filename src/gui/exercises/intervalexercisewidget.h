#ifndef INTERVALEXERCISEWIDGET_H
#define INTERVALEXERCISEWIDGET_H

#include <QWidget>
#include "../../audio/audio.h"
#include "../common/notetileswidget.h"

namespace Ui {
class IntervalExerciseWidget;
}

class IntervalExerciseWidget : public QWidget //переделать на наследуемый
{
    Q_OBJECT

public:
    explicit IntervalExerciseWidget(NotePlayer* notePlayer, QWidget *parent = nullptr);
    ~IntervalExerciseWidget();

    void playTone();
    QVector<QString> correctAnswer;
    QVector<QString>  userAnswer;
signals:
    void inputFinished();
    void requestSetMode(NoteTilesWidget::Mode);
private:
    Ui::IntervalExerciseWidget *ui;
    AudioProcessor *processor;
    NotePlayer* notePlayer;
    NoteTilesWidget *tiles;
    int noteCounter = 0;
};

#endif // INTERVALEXERCISEWIDGET_H
