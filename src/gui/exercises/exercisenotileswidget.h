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
    void addDirectionSelector();
    void showResult(const QString& correct);
    void exercisePlayFinished() override;
    void showDirectionResult(const QString& correct);
signals:
    void answerSelected(const QString& answer);
    void directionSelected(const QString& direction);
private:
    void resetSelection();
    void btnsEnable(bool status);
    void refreshStyle(QWidget* w);
private:
    Ui::ExerciseNoTilesWidget *ui;
    QPushButton* selectedBtn;
    QButtonGroup* directionGroup = nullptr;
};

#endif // EXERCISENOTILESWIDGET_H
