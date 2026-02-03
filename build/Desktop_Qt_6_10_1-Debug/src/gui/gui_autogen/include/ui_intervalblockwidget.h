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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntervalBlockWidget
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QPushButton *backBtn;
    QPushButton *exercise1Btn;

    void setupUi(QWidget *IntervalBlockWidget)
    {
        if (IntervalBlockWidget->objectName().isEmpty())
            IntervalBlockWidget->setObjectName("IntervalBlockWidget");
        IntervalBlockWidget->resize(400, 300);
        formLayoutWidget = new QWidget(IntervalBlockWidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(69, 39, 271, 231));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        backBtn = new QPushButton(formLayoutWidget);
        backBtn->setObjectName("backBtn");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, backBtn);

        exercise1Btn = new QPushButton(formLayoutWidget);
        exercise1Btn->setObjectName("exercise1Btn");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, exercise1Btn);


        retranslateUi(IntervalBlockWidget);

        QMetaObject::connectSlotsByName(IntervalBlockWidget);
    } // setupUi

    void retranslateUi(QWidget *IntervalBlockWidget)
    {
        IntervalBlockWidget->setWindowTitle(QCoreApplication::translate("IntervalBlockWidget", "Form", nullptr));
        backBtn->setText(QCoreApplication::translate("IntervalBlockWidget", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        exercise1Btn->setText(QCoreApplication::translate("IntervalBlockWidget", "\320\236\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntervalBlockWidget: public Ui_IntervalBlockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERVALBLOCKWIDGET_H
