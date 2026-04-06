#ifndef EXERCISENOTILESWIDGET_H
#define EXERCISENOTILESWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
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
    void exercisePlayFinished() override;
signals:
    void answerSelected(const QString& answer);
    void difficultyChanged(int level);
private:
    void resetSelection();
    void btnsEnable(bool status);
    void refreshStyle(QWidget* w);
private:
    Ui::ExerciseNoTilesWidget *ui;
    QPushButton* selectedBtn;
};

#endif // EXERCISENOTILESWIDGET_H
