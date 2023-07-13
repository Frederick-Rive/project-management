/********************************************************************************
** Form generated from reading UI file 'adminscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINSCREEN_H
#define UI_ADMINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminScreen
{
public:

    void setupUi(QWidget *AdminScreen)
    {
        if (AdminScreen->objectName().isEmpty())
            AdminScreen->setObjectName(QString::fromUtf8("AdminScreen"));
        AdminScreen->resize(778, 526);

        retranslateUi(AdminScreen);

        QMetaObject::connectSlotsByName(AdminScreen);
    } // setupUi

    void retranslateUi(QWidget *AdminScreen)
    {
        AdminScreen->setWindowTitle(QCoreApplication::translate("AdminScreen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminScreen: public Ui_AdminScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINSCREEN_H
