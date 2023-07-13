/********************************************************************************
** Form generated from reading UI file 'ganttchart.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GANTTCHART_H
#define UI_GANTTCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GanttChart
{
public:

    void setupUi(QWidget *GanttChart)
    {
        if (GanttChart->objectName().isEmpty())
            GanttChart->setObjectName(QString::fromUtf8("GanttChart"));
        GanttChart->resize(660, 418);
        GanttChart->setMinimumSize(QSize(660, 418));
        GanttChart->setMaximumSize(QSize(660, 418));

        retranslateUi(GanttChart);

        QMetaObject::connectSlotsByName(GanttChart);
    } // setupUi

    void retranslateUi(QWidget *GanttChart)
    {
        GanttChart->setWindowTitle(QCoreApplication::translate("GanttChart", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GanttChart: public Ui_GanttChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GANTTCHART_H
