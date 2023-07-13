/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *kanbanButton;
    QPushButton *ganttButton;
    QPushButton *adminButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *minimiseButton;
    QPushButton *closeButton;
    QHBoxLayout *horizontalLayout;
    QWidget *leftWidget;
    QVBoxLayout *leftLayout;
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1600, 900);
        MainWindow->setMinimumSize(QSize(1600, 900));
        MainWindow->setMaximumSize(QSize(1600, 900));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(1600, 900));
        centralwidget->setMaximumSize(QSize(1600, 900));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QWidget(centralwidget);
        headerWidget->setObjectName(QString::fromUtf8("headerWidget"));
        headerWidget->setMinimumSize(QSize(0, 64));
        headerWidget->setMaximumSize(QSize(16777215, 64));
        headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setSpacing(0);
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        headerLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(240, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        kanbanButton = new QPushButton(headerWidget);
        kanbanButton->setObjectName(QString::fromUtf8("kanbanButton"));
        kanbanButton->setMinimumSize(QSize(280, 64));
        kanbanButton->setMaximumSize(QSize(280, 64));
        QFont font;
        font.setPointSize(18);
        kanbanButton->setFont(font);

        headerLayout->addWidget(kanbanButton);

        ganttButton = new QPushButton(headerWidget);
        ganttButton->setObjectName(QString::fromUtf8("ganttButton"));
        ganttButton->setMinimumSize(QSize(280, 64));
        ganttButton->setMaximumSize(QSize(280, 64));
        ganttButton->setFont(font);

        headerLayout->addWidget(ganttButton);

        adminButton = new QPushButton(headerWidget);
        adminButton->setObjectName(QString::fromUtf8("adminButton"));
        adminButton->setMinimumSize(QSize(280, 64));
        adminButton->setMaximumSize(QSize(280, 64));
        adminButton->setFont(font);

        headerLayout->addWidget(adminButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(horizontalSpacer_2);

        minimiseButton = new QPushButton(headerWidget);
        minimiseButton->setObjectName(QString::fromUtf8("minimiseButton"));
        minimiseButton->setMinimumSize(QSize(64, 64));
        minimiseButton->setMaximumSize(QSize(64, 64));
        minimiseButton->setFont(font);

        headerLayout->addWidget(minimiseButton);

        closeButton = new QPushButton(headerWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setMinimumSize(QSize(64, 64));
        closeButton->setMaximumSize(QSize(64, 64));
        closeButton->setFont(font);

        headerLayout->addWidget(closeButton);


        verticalLayout->addWidget(headerWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName(QString::fromUtf8("leftWidget"));
        leftWidget->setMinimumSize(QSize(240, 836));
        leftWidget->setMaximumSize(QSize(240, 836));
        leftLayout = new QVBoxLayout(leftWidget);
        leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
        leftLayout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(leftWidget);

        mainWidget = new QWidget(centralwidget);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        mainWidget->setMaximumSize(QSize(16777215, 1300));
        mainLayout = new QVBoxLayout(mainWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(mainWidget);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        kanbanButton->setText(QCoreApplication::translate("MainWindow", "Kanban Board", nullptr));
        ganttButton->setText(QCoreApplication::translate("MainWindow", "Gantt Chart", nullptr));
        adminButton->setText(QCoreApplication::translate("MainWindow", "Admin", nullptr));
        minimiseButton->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
