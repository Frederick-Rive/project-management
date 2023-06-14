#include "ganttchart.h"
#include "ui_ganttchart.h"

GanttChart::GanttChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GanttChart)
{
    ui->setupUi(this);
}

GanttChart::~GanttChart()
{
    delete ui;
}
