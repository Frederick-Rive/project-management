/********************************************************************************
** Form generated from reading UI file 'kanbanboard.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KANBANBOARD_H
#define UI_KANBANBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KanbanBoard
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *vert;
    QLabel *label;
    QWidget *verticalWidget;
    QVBoxLayout *todoLayout;
    QPushButton *addNewButton;
    QVBoxLayout *vert_2;
    QLabel *label_2;
    QWidget *verticalWidget_2;
    QVBoxLayout *inprogressLayout;
    QVBoxLayout *vert_3;
    QLabel *label_3;
    QWidget *verticalWidget_3;
    QVBoxLayout *completedLayout;

    void setupUi(QWidget *KanbanBoard)
    {
        if (KanbanBoard->objectName().isEmpty())
            KanbanBoard->setObjectName(QString::fromUtf8("KanbanBoard"));
        KanbanBoard->resize(1360, 836);
        KanbanBoard->setMinimumSize(QSize(1360, 836));
        KanbanBoard->setMaximumSize(QSize(1360, 836));
        KanbanBoard->setStyleSheet(QString::fromUtf8("background-color: #fff;"));
        horizontalLayout = new QHBoxLayout(KanbanBoard);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 30, 20, 0);
        vert = new QVBoxLayout();
        vert->setSpacing(20);
        vert->setObjectName(QString::fromUtf8("vert"));
        vert->setSizeConstraint(QLayout::SetDefaultConstraint);
        vert->setContentsMargins(5, 0, 5, -1);
        label = new QLabel(KanbanBoard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(380, 68));
        label->setMaximumSize(QSize(380, 68));
        QFont font;
        font.setPointSize(22);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignCenter);

        vert->addWidget(label);

        verticalWidget = new QWidget(KanbanBoard);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setMinimumSize(QSize(380, 0));
        verticalWidget->setMaximumSize(QSize(380, 9999));
        verticalWidget->setStyleSheet(QString::fromUtf8(""));
        todoLayout = new QVBoxLayout(verticalWidget);
        todoLayout->setSpacing(5);
        todoLayout->setObjectName(QString::fromUtf8("todoLayout"));
        todoLayout->setContentsMargins(20, 0, 20, 0);
        addNewButton = new QPushButton(verticalWidget);
        addNewButton->setObjectName(QString::fromUtf8("addNewButton"));
        addNewButton->setMinimumSize(QSize(48, 48));
        addNewButton->setMaximumSize(QSize(48, 48));
        QFont font1;
        font1.setPointSize(30);
        font1.setBold(true);
        font1.setKerning(true);
        addNewButton->setFont(font1);
        addNewButton->setStyleSheet(QString::fromUtf8("background-color: #fff; color: #6096BA"));
        addNewButton->setFlat(true);

        todoLayout->addWidget(addNewButton);


        vert->addWidget(verticalWidget);


        horizontalLayout->addLayout(vert);

        vert_2 = new QVBoxLayout();
        vert_2->setSpacing(20);
        vert_2->setObjectName(QString::fromUtf8("vert_2"));
        vert_2->setContentsMargins(5, -1, 5, -1);
        label_2 = new QLabel(KanbanBoard);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(380, 68));
        label_2->setMaximumSize(QSize(380, 68));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignCenter);

        vert_2->addWidget(label_2);

        verticalWidget_2 = new QWidget(KanbanBoard);
        verticalWidget_2->setObjectName(QString::fromUtf8("verticalWidget_2"));
        verticalWidget_2->setMinimumSize(QSize(380, 0));
        verticalWidget_2->setMaximumSize(QSize(380, 9999));
        verticalWidget_2->setStyleSheet(QString::fromUtf8(""));
        inprogressLayout = new QVBoxLayout(verticalWidget_2);
        inprogressLayout->setSpacing(5);
        inprogressLayout->setObjectName(QString::fromUtf8("inprogressLayout"));
        inprogressLayout->setContentsMargins(20, 0, 20, 0);

        vert_2->addWidget(verticalWidget_2);


        horizontalLayout->addLayout(vert_2);

        vert_3 = new QVBoxLayout();
        vert_3->setSpacing(20);
        vert_3->setObjectName(QString::fromUtf8("vert_3"));
        vert_3->setContentsMargins(5, -1, 5, -1);
        label_3 = new QLabel(KanbanBoard);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(380, 68));
        label_3->setMaximumSize(QSize(380, 68));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setAlignment(Qt::AlignCenter);

        vert_3->addWidget(label_3);

        verticalWidget_3 = new QWidget(KanbanBoard);
        verticalWidget_3->setObjectName(QString::fromUtf8("verticalWidget_3"));
        verticalWidget_3->setMinimumSize(QSize(380, 0));
        verticalWidget_3->setMaximumSize(QSize(380, 9999));
        verticalWidget_3->setStyleSheet(QString::fromUtf8(""));
        completedLayout = new QVBoxLayout(verticalWidget_3);
        completedLayout->setSpacing(5);
        completedLayout->setObjectName(QString::fromUtf8("completedLayout"));
        completedLayout->setContentsMargins(20, 0, 20, 0);

        vert_3->addWidget(verticalWidget_3);


        horizontalLayout->addLayout(vert_3);


        retranslateUi(KanbanBoard);

        QMetaObject::connectSlotsByName(KanbanBoard);
    } // setupUi

    void retranslateUi(QWidget *KanbanBoard)
    {
        KanbanBoard->setWindowTitle(QCoreApplication::translate("KanbanBoard", "Form", nullptr));
        label->setText(QCoreApplication::translate("KanbanBoard", "To Do", nullptr));
        addNewButton->setText(QCoreApplication::translate("KanbanBoard", "+", nullptr));
        label_2->setText(QCoreApplication::translate("KanbanBoard", "In Progress", nullptr));
        label_3->setText(QCoreApplication::translate("KanbanBoard", "Completed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KanbanBoard: public Ui_KanbanBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KANBANBOARD_H
