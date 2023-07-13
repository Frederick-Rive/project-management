/********************************************************************************
** Form generated from reading UI file 'notification.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIFICATION_H
#define UI_NOTIFICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Notification
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QFrame *line;

    void setupUi(QWidget *Notification)
    {
        if (Notification->objectName().isEmpty())
            Notification->setObjectName(QString::fromUtf8("Notification"));
        Notification->resize(240, 80);
        Notification->setMinimumSize(QSize(240, 80));
        Notification->setMaximumSize(QSize(240, 16777215));
        verticalLayout = new QVBoxLayout(Notification);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QLabel(Notification);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(0, 40));
        title->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setPointSize(16);
        title->setFont(font);

        verticalLayout->addWidget(title);

        line = new QFrame(Notification);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        retranslateUi(Notification);

        QMetaObject::connectSlotsByName(Notification);
    } // setupUi

    void retranslateUi(QWidget *Notification)
    {
        Notification->setWindowTitle(QCoreApplication::translate("Notification", "Form", nullptr));
        title->setText(QCoreApplication::translate("Notification", "title", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Notification: public Ui_Notification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIFICATION_H
