/********************************************************************************
** Form generated from reading UI file 'intervalblockwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERVALBLOCKWIDGET_H
#define UI_INTERVALBLOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntervalBlockWidget
{
public:

    void setupUi(QWidget *IntervalBlockWidget)
    {
        if (IntervalBlockWidget->objectName().isEmpty())
            IntervalBlockWidget->setObjectName("IntervalBlockWidget");
        IntervalBlockWidget->resize(400, 300);

        retranslateUi(IntervalBlockWidget);

        QMetaObject::connectSlotsByName(IntervalBlockWidget);
    } // setupUi

    void retranslateUi(QWidget *IntervalBlockWidget)
    {
        IntervalBlockWidget->setWindowTitle(QCoreApplication::translate("IntervalBlockWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntervalBlockWidget: public Ui_IntervalBlockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALBLOCKWIDGET_H
