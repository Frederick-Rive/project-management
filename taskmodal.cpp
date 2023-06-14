#include "taskmodal.h"
#include "ui_taskmodal.h"

TaskModal::TaskModal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskModal)
{
    ui->setupUi(this);
}

void TaskModal::setTitle(std::string input) {
    ui->title->setText(QString::fromStdString(input));
}
void TaskModal::setDescription(std::string input) {
    ui->description->setText(QString::fromStdString(input));
}
void TaskModal::setStartDate(project::Date* input) {
    ui->startDate->setText(QString::fromStdString(input->getDateString()));
}
void TaskModal::setEndDate(project::Date* input) {
    ui->endDate->setText(QString::fromStdString(input->getDateString()));
}
void TaskModal::addUser(project::UserAccess* input) {
    return;
}
void TaskModal::removeUser(int input) {
    return;
}

TaskModal::~TaskModal()
{
    delete ui;
}
