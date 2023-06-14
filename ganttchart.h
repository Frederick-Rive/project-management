#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QWidget>

namespace Ui {
class GanttChart;
}

class GanttChart : public QWidget
{
    Q_OBJECT

public:
    explicit GanttChart(QWidget *parent = nullptr);
    ~GanttChart();

private:
    Ui::GanttChart *ui;
};

#endif // GANTTCHART_H
