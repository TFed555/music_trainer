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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntervalExerciseWidget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *stopBtn;
    QPushButton *playBtn;

    void setupUi(QWidget *IntervalExerciseWidget)
    {
        if (IntervalExerciseWidget->objectName().isEmpty())
            IntervalExerciseWidget->setObjectName("IntervalExerciseWidget");
        IntervalExerciseWidget->resize(400, 300);
        horizontalLayoutWidget = new QWidget(IntervalExerciseWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(50, 110, 311, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stopBtn = new QPushButton(horizontalLayoutWidget);
        stopBtn->setObjectName("stopBtn");

        horizontalLayout->addWidget(stopBtn);

        playBtn = new QPushButton(horizontalLayoutWidget);
        playBtn->setObjectName("playBtn");

        horizontalLayout->addWidget(playBtn);


        retranslateUi(IntervalExerciseWidget);

        QMetaObject::connectSlotsByName(IntervalExerciseWidget);
    } // setupUi

    void retranslateUi(QWidget *IntervalExerciseWidget)
    {
        IntervalExerciseWidget->setWindowTitle(QCoreApplication::translate("IntervalExerciseWidget", "Form", nullptr));
        stopBtn->setText(QCoreApplication::translate("IntervalExerciseWidget", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        playBtn->setText(QCoreApplication::translate("IntervalExerciseWidget", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntervalExerciseWidget: public Ui_IntervalExerciseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALEXERCISEWIDGET_H
