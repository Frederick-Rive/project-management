#include "kanbanwidget.h"
#include "ui_kanbanwidget.h"

KanbanWidget::KanbanWidget(project::Task *t, MainWindow *m, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanbanWidget)
{
    ui->setupUi(this);

    task = t;
    mainWindow = m;

    ui->title->setText(QString::fromStdString(task->getName()));

    ui->verticalWidget->setStyleSheet("background-color: #A3CEF1; font-size: 18px; border-radius: 5px; color: #000");
}

KanbanWidget::~KanbanWidget()
{
    delete ui;
}

void KanbanWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mainWindow->OpenTaskModal(task);
    }
    return;
}
