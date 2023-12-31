#include "kanbanboard.h"
#include "ui_kanbanboard.h"
#include "taskmodal.h"

KanbanBoard::KanbanBoard(MainWindow *m, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanbanBoard)
{
    ui->setupUi(this);

    mainWindow = m;

    this->setStyleSheet("QWidget { background-color: #fff; } QLabel { background-color: #6096BA; color:#fff; }");

    ui->todoLayout->addStretch();
    ui->inprogressLayout->addStretch();
    ui->completedLayout->addStretch();

    //Automatically call GetNewTask function whenever a new task is added in the MainWindow
    connect(mainWindow , &MainWindow::taskAdded, this, &KanbanBoard::GetNewTask);
}

KanbanBoard::~KanbanBoard()
{
    delete ui;
}

// Create a new KanbanWidget based on a Task, and add it to the Kanban Board
void KanbanBoard::AddTask(int state, project::Task* task) {
    KanbanWidget *newWidget = new KanbanWidget(task, mainWindow, this);
    switch(state){
    case 0:
        ui->todoLayout->insertWidget(ui->todoLayout->children().size(), newWidget);
        break;
    case 1:
        ui->inprogressLayout->insertWidget(ui->todoLayout->children().size(), newWidget);
        break;
    case 2:
        ui->completedLayout->insertWidget(ui->todoLayout->children().size(), newWidget);
        break;
    }
    //newWidget->installEventFilter(this);
}

void KanbanBoard::RemoveTask(int state, int index) {

}
void KanbanBoard::ClearTasks() {

}

//Get latest task from the MainWindow
void KanbanBoard::GetNewTask(int state) {
    AddTask(state, mainWindow->GetLatestTask(state));
}

// Handles dragging Kanban Widgets (inactive)
bool KanbanBoard::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            active = dynamic_cast<KanbanWidget*>(obj);
            startPos = (mouseEvent->globalPosition() - active->frameGeometry().topLeft()).toPoint();
            qDebug() << mouseEvent->globalPosition();
            return false;
        }
    } else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton)
        {
            //qDebug() << startPos;
            active->move(mouseEvent->globalPosition().toPoint() - startPos);
            return false;
        }
    }
    return false;
}


void KanbanBoard::on_addNewButton_clicked()
{
    mainWindow->OpenTaskModal(nullptr);
}

