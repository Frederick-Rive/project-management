#include "notification.h"
#include "ui_notification.h"

Notification::Notification(QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notification)
{
    ui->setupUi(this);

    ui->title->setText(title);
    this->setStyleSheet("background-color: #E7ECEF;");
}

Notification::~Notification()
{
    delete ui;
}
