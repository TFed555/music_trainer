#ifndef EXERCISENOTILESWIDGET_H
#define EXERCISENOTILESWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"

namespace Ui {
class ExerciseNoTilesWidget;
}

class ExerciseNoTilesWidget : public IExerciseWidget
{
    Q_OBJECT

public:
    explicit ExerciseNoTilesWidget(QWidget *parent = nullptr);
    ~ExerciseNoTilesWidget();
public slots:
    void addAnswers(QVector<QString> answers);
    void showResult(const QString& correct);
    void requestAnswerSlot();
signals:
    void answerSelected(const QString& answer);
    void requestAnswers();
private:
    Ui::ExerciseNoTilesWidget *ui;
};

#endif // EXERCISENOTILESWIDGET_H
