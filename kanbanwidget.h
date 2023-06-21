#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <mainwindow.h>
#include "projectobjects.h"

namespace Ui {
class KanbanWidget;
}

class KanbanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KanbanWidget(project::Task *t, MainWindow *m, QWidget *parent = nullptr);
    ~KanbanWidget();
private:
    int index;
    project::Task *task;
    MainWindow *mainWindow;
    Ui::KanbanWidget *ui;

    void mousePressEvent(QMouseEvent *event);
};

#endif // KANBANWIDGET_H
