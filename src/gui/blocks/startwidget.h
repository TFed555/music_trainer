#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "../../core/common/interfaces/IExerciseWidget.h"
#include "../../core/common/models/ExerciseType.h"
#include <QVBoxLayout>


class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();
    enum class BlockCategory {
        Intervals,
        Chords,
        Notes,
        Rhythm,
        Melody
    };
    struct BlockConfig {
        QVector<ExerciseType> exercises;
    };

    void setBlock(int block);
signals:
    void exerciseSelected(ExerciseType);
protected:
    void changeEvent(QEvent* event) override;
private:
    void clearButtons();
    void addButton(const QString& title, ExerciseType type);
    QVBoxLayout* layout;
    // using BlockConfig = QVector<ExerciseType>;
    static const QMap<BlockCategory, BlockConfig> blockConfigs;
    int currentBlock;
};

#endif // STARTWIDGET_H
