/********************************************************************************
** Form generated from reading UI file 'mainmenuwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENUWIDGET_H
#define UI_MAINMENUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenuWidget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *intervalBtn;

    void setupUi(QWidget *MainMenuWidget)
    {
        if (MainMenuWidget->objectName().isEmpty())
            MainMenuWidget->setObjectName("MainMenuWidget");
        MainMenuWidget->resize(400, 300);
        gridLayoutWidget = new QWidget(MainMenuWidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(50, 40, 311, 221));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        intervalBtn = new QPushButton(gridLayoutWidget);
        intervalBtn->setObjectName("intervalBtn");

        gridLayout->addWidget(intervalBtn, 0, 0, 1, 1);


        retranslateUi(MainMenuWidget);

        QMetaObject::connectSlotsByName(MainMenuWidget);
    } // setupUi

    void retranslateUi(QWidget *MainMenuWidget)
    {
        MainMenuWidget->setWindowTitle(QCoreApplication::translate("MainMenuWidget", "Form", nullptr));
        intervalBtn->setText(QCoreApplication::translate("MainMenuWidget", "\320\230\320\275\321\202\320\265\321\200\320\262\320\260\320\273\321\214\320\275\321\213\320\265 \321\203\320\277\321\200\320\260\320\266\320\275\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenuWidget: public Ui_MainMenuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENUWIDGET_H
