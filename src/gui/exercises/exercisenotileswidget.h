#ifndef EXERCISENOTILESWIDGET_H
#define EXERCISENOTILESWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../../core/common/models/Mode.h"
#include <QPushButton>

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
    void exercisePlayFinished() override;
signals:
    void answerSelected(const QString& answer);
    void requestAnswers();
private:
    void highlightBtn(Mode, QPushButton*);
    void resetSelection();
    void btnsEnable(bool status);
private:
    Ui::ExerciseNoTilesWidget *ui;
    QPushButton* selectedBtn;
};

#endif // EXERCISENOTILESWIDGET_H
