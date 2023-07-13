/********************************************************************************
** Form generated from reading UI file 'kanbanwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KANBANWIDGET_H
#define UI_KANBANWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KanbanWidget
{
public:
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *title;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *KanbanWidget)
    {
        if (KanbanWidget->objectName().isEmpty())
            KanbanWidget->setObjectName(QString::fromUtf8("KanbanWidget"));
        KanbanWidget->resize(340, 150);
        KanbanWidget->setMinimumSize(QSize(340, 150));
        KanbanWidget->setMaximumSize(QSize(340, 150));
        KanbanWidget->setAutoFillBackground(false);
        verticalWidget = new QWidget(KanbanWidget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setGeometry(QRect(0, 0, 340, 150));
        verticalWidget->setMinimumSize(QSize(340, 150));
        verticalWidget->setMaximumSize(QSize(340, 150));
        verticalLayout_2 = new QVBoxLayout(verticalWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        title = new QLabel(verticalWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(340, 76));
        title->setMaximumSize(QSize(340, 76));
        QFont font;
        font.setPointSize(26);
        title->setFont(font);
        title->setMargin(5);

        verticalLayout_2->addWidget(title);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(KanbanWidget);

        QMetaObject::connectSlotsByName(KanbanWidget);
    } // setupUi

    void retranslateUi(QWidget *KanbanWidget)
    {
        KanbanWidget->setWindowTitle(QCoreApplication::translate("KanbanWidget", "Form", nullptr));
        title->setText(QCoreApplication::translate("KanbanWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KanbanWidget: public Ui_KanbanWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KANBANWIDGET_H
