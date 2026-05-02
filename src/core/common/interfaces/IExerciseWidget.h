#ifndef IEXERCISEWIDGET_H
#define IEXERCISEWIDGET_H

#include <QWidget>
#include <QEvent>

class IExerciseWidget : public QWidget {
    Q_OBJECT
public:
    explicit IExerciseWidget(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IExerciseWidget() {};
public slots:
    virtual void exercisePlayFinished() = 0;
    virtual void setDescription(const QString& text) = 0;
protected:
    void changeEvent(QEvent* event) {
        if (event->type() == QEvent::LanguageChange) {
            retranslate();
        }
        QWidget::changeEvent(event);
    }
    QVector<QString> getDifficultyItems() const {
        return { tr("Легко"), tr("Сложно") };
    }
private:
    virtual void retranslate() = 0;
signals:
    void startClicked();
    void stopClicked();
    void backClicked();
    void replayClicked();
    void langChange();
};

#endif // IEXERCISEWIDGET_H
