/********************************************************************************
** Form generated from reading UI file 'intervalexercisewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERVALEXERCISEWIDGET_H
#define UI_INTERVALEXERCISEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntervalExerciseWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *IntervalExerciseWidget)
    {
        if (IntervalExerciseWidget->objectName().isEmpty())
            IntervalExerciseWidget->setObjectName("IntervalExerciseWidget");
        IntervalExerciseWidget->resize(567, 396);
        verticalLayoutWidget = new QWidget(IntervalExerciseWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(150, 20, 231, 121));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        startBtn = new QPushButton(verticalLayoutWidget);
        startBtn->setObjectName("startBtn");

        verticalLayout->addWidget(startBtn);

        stopBtn = new QPushButton(verticalLayoutWidget);
        stopBtn->setObjectName("stopBtn");

        verticalLayout->addWidget(stopBtn);

        horizontalLayoutWidget = new QWidget(IntervalExerciseWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(30, 180, 491, 191));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(IntervalExerciseWidget);

        QMetaObject::connectSlotsByName(IntervalExerciseWidget);
    } // setupUi

    void retranslateUi(QWidget *IntervalExerciseWidget)
    {
        IntervalExerciseWidget->setWindowTitle(QCoreApplication::translate("IntervalExerciseWidget", "Form", nullptr));
        startBtn->setText(QCoreApplication::translate("IntervalExerciseWidget", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        stopBtn->setText(QCoreApplication::translate("IntervalExerciseWidget", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntervalExerciseWidget: public Ui_IntervalExerciseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALEXERCISEWIDGET_H
