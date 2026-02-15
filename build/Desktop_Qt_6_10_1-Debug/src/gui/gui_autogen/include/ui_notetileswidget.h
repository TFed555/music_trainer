/********************************************************************************
** Form generated from reading UI file 'notetileswidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTETILESWIDGET_H
#define UI_NOTETILESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoteTilesWidget
{
public:

    void setupUi(QWidget *NoteTilesWidget)
    {
        if (NoteTilesWidget->objectName().isEmpty())
            NoteTilesWidget->setObjectName("NoteTilesWidget");
        NoteTilesWidget->resize(400, 300);

        retranslateUi(NoteTilesWidget);

        QMetaObject::connectSlotsByName(NoteTilesWidget);
    } // setupUi

    void retranslateUi(QWidget *NoteTilesWidget)
    {
        NoteTilesWidget->setWindowTitle(QCoreApplication::translate("NoteTilesWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoteTilesWidget: public Ui_NoteTilesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTETILESWIDGET_H
