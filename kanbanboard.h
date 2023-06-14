#ifndef KANBANBOARD_H
#define KANBANBOARD_H

#include <QWidget>
#include <kanbanwidget.h>
#include <projectobjects.h>

namespace Ui {
class KanbanBoard;
}

class KanbanBoard : public QWidget
{
    Q_OBJECT

public:
    explicit KanbanBoard(QWidget *parent = nullptr);
    ~KanbanBoard();
    void AddTask(int state, project::Task* task);
    void RemoveTask(int state, int index);
    void ClearTasks();

private:
    Ui::KanbanBoard *ui;
    std::vector<project::Task*> todoList, progressList, completedList;
};

#endif // KANBANBOARD_H
