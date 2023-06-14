#include "kanbanwidget.h"
#include "ui_kanbanwidget.h"

KanbanWidget::KanbanWidget(std::string name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanbanWidget)
{
    ui->setupUi(this);

    ui->title->setText(QString::fromStdString(name));

    this->setStyleSheet("background-color: #A3CEF1; font-size: 12px; border-radius: 5px; color: #000");
}

KanbanWidget::~KanbanWidget()
{
    delete ui;
}

void KanbanWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        return;
    }
    return;
}
