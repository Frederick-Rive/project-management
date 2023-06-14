#include "kanbanboard.h"
#include "ui_kanbanboard.h"

KanbanBoard::KanbanBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanbanBoard)
{
    ui->setupUi(this);

    this->setStyleSheet("QWidget { background-color: #fff; } QLabel { background-color: #6096BA; color:#fff; }");

    std::string name = "Finish the FUCKING aesthetics", desc = "pleaaase";

    project::Task *testTask = new project::Task(name, desc, new project::Date(20, 5, 2023), new project::Date(22, 5, 2023));

    ui->todoLayout->addStretch();
    ui->inprogressLayout->addStretch();
    ui->completedLayout->addStretch();

    this->AddTask(0, testTask);
}

KanbanBoard::~KanbanBoard()
{
    delete ui;
}

void KanbanBoard::AddTask(int state, project::Task* task) {
    KanbanWidget *newWidget = new KanbanWidget(task->getName(), this);
    switch(state){
    case 0:
        ui->todoLayout->insertWidget(this->todoList.size(), newWidget);
        this->todoList.push_back(task);
        break;
    case 1:
        ui->inprogressLayout->insertWidget(this->progressList.size(), newWidget);
        this->todoList.push_back(task);
        break;
    case 2:
        ui->completedLayout->insertWidget(this->completedList.size(), newWidget);
        this->completedList.push_back(task);
        break;
    }
}
void KanbanBoard::RemoveTask(int state, int index) {

}
void KanbanBoard::ClearTasks() {

}
