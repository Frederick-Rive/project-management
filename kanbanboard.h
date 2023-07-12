#ifndef KANBANBOARD_H
#define KANBANBOARD_H

#include <QWidget>
#include <kanbanwidget.h>
#include <projectobjects.h>
#include "mainwindow.h"

namespace Ui {
class KanbanBoard;
}

class KanbanBoard : public QWidget
{
    Q_OBJECT

public:
    explicit KanbanBoard(MainWindow *m, QWidget *parent = nullptr);
    ~KanbanBoard();
    void AddTask(int state, project::Task* task);
    void RemoveTask(int state, int index);
    void ClearTasks();

private:
    Ui::KanbanBoard *ui;
    MainWindow *mainWindow;
    QPoint startPos;

    KanbanWidget *active;

    //void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter (QObject *obj, QEvent *event);

private slots:
    void GetNewTask(int state);
    void on_addNewButton_clicked();
};

#endif // KANBANBOARD_H
