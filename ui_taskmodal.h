/********************************************************************************
** Form generated from reading UI file 'taskmodal.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMODAL_H
#define UI_TASKMODAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskModal
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *background;
    QGridLayout *gridLayout;
    QWidget *mainWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *header;
    QHBoxLayout *horizontalLayout;
    QLineEdit *title;
    QDateEdit *startDate;
    QDateEdit *endDate;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *stateCombo;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *description;
    QFrame *line;
    QGridLayout *usersGrid;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveButton;

    void setupUi(QWidget *TaskModal)
    {
        if (TaskModal->objectName().isEmpty())
            TaskModal->setObjectName(QString::fromUtf8("TaskModal"));
        TaskModal->resize(1360, 840);
        TaskModal->setMinimumSize(QSize(1360, 840));
        TaskModal->setMaximumSize(QSize(1360, 840));
        verticalLayout = new QVBoxLayout(TaskModal);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        background = new QWidget(TaskModal);
        background->setObjectName(QString::fromUtf8("background"));
        gridLayout = new QGridLayout(background);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mainWidget = new QWidget(background);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        mainWidget->setMinimumSize(QSize(760, 440));
        mainWidget->setMaximumSize(QSize(760, 440));
        verticalLayout_2 = new QVBoxLayout(mainWidget);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        header = new QWidget(mainWidget);
        header->setObjectName(QString::fromUtf8("header"));
        header->setMinimumSize(QSize(0, 40));
        header->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(header);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        title = new QLineEdit(header);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(0, 32));
        QFont font;
        font.setPointSize(12);
        title->setFont(font);

        horizontalLayout->addWidget(title);

        startDate = new QDateEdit(header);
        startDate->setObjectName(QString::fromUtf8("startDate"));
        startDate->setMinimumSize(QSize(0, 32));
        QFont font1;
        font1.setPointSize(10);
        startDate->setFont(font1);

        horizontalLayout->addWidget(startDate);

        endDate = new QDateEdit(header);
        endDate->setObjectName(QString::fromUtf8("endDate"));
        endDate->setMinimumSize(QSize(0, 32));
        endDate->setFont(font1);

        horizontalLayout->addWidget(endDate);


        verticalLayout_2->addWidget(header);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        stateCombo = new QComboBox(mainWidget);
        stateCombo->setObjectName(QString::fromUtf8("stateCombo"));
        stateCombo->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(stateCombo);

        horizontalSpacer_2 = new QSpacerItem(400, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        description = new QTextEdit(mainWidget);
        description->setObjectName(QString::fromUtf8("description"));

        verticalLayout_2->addWidget(description);

        line = new QFrame(mainWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        usersGrid = new QGridLayout();
        usersGrid->setObjectName(QString::fromUtf8("usersGrid"));
        usersGrid->setContentsMargins(5, 5, 5, 5);

        verticalLayout_2->addLayout(usersGrid);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        saveButton = new QPushButton(mainWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setMinimumSize(QSize(90, 30));
        saveButton->setFont(font);

        horizontalLayout_2->addWidget(saveButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addWidget(mainWidget, 0, 0, 1, 1);


        verticalLayout->addWidget(background);


        retranslateUi(TaskModal);

        QMetaObject::connectSlotsByName(TaskModal);
    } // setupUi

    void retranslateUi(QWidget *TaskModal)
    {
        TaskModal->setWindowTitle(QCoreApplication::translate("TaskModal", "Form", nullptr));
        saveButton->setText(QCoreApplication::translate("TaskModal", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskModal: public Ui_TaskModal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKMODAL_H
