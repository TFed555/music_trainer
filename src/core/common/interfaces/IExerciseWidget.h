#ifndef IEXERCISEWIDGET_H
#define IEXERCISEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QComboBox>
#include <QMessageBox>

class IExerciseWidget : public QWidget {
    Q_OBJECT
public:
    explicit IExerciseWidget(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IExerciseWidget() {};
public slots:
    virtual void exercisePlayFinished() = 0;
    virtual void setDescription(const QString& text) = 0;
    void showErrorInfo(const QString& err) {
        QMessageBox::warning(this, "Music Trainer", err, QMessageBox::Ok);
    }
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

    static void retranslateComboBox(QComboBox* box, const QVector<QString>& items) {
        int idx = box->currentIndex();
        box->blockSignals(true);
        box->clear();
        for (const auto& item : items) box->addItem(item);
        box->setCurrentIndex(idx);
        box->blockSignals(false);
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
