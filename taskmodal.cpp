#include "taskmodal.h"
#include "ui_taskmodal.h"
#include "mainwindow.h"

TaskModal::TaskModal(project::Task *t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskModal)
{
    ui->setupUi(this);

    ui->stateCombo->addItem("To Do");
    ui->stateCombo->addItem("In Progress");
    ui->stateCombo->addItem("Completed");

    if (t != nullptr) {
        task = t;

        this->setTitle(task->getName());
        this->setDescription(task->getDescription());
        this->setStartDate(task->getStartDate());
        this->setEndDate(task->getEndDate());
        this->setState(task->getState());
    } else {
        task = nullptr;
    }

    ui->startDate->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->endDate->setButtonSymbols(QAbstractSpinBox::NoButtons);

    this->setStyleSheet(
                        "QWidget#background { background-color: rgba(0,0,0,0.6); }"
                        "QWidget#mainWidget { border-radius: 5px; }"
                        "QLineEdit { border-radius: 0; border: 1px solid #5096aA; }"
                        "QDateEdit { border-radius: 0; border: 1px solid #5096aA; }"
                        "QDateEdit { border-radius: 0; border: 1px solid #5096aA; }"
                        "QTextEdit { border-radius: 0; border: 1px solid #5096aA; }"
                        "QComboBox { border-radius: 0; border: 1px solid #5096aA; }"
                        "QComboBox::drop-down { color: #5096aA; background-color: #fff; }"
                        "QPushButton { border-radius: 3px; }"
                        );
}

void TaskModal::setTitle(std::string input) {
    ui->title->setText(QString::fromStdString(input));
}
void TaskModal::setDescription(std::string input) {
    ui->description->setText(QString::fromStdString(input));
}
void TaskModal::setStartDate(project::Date input) {
    QDate d = QDate(input.getDate(), input.getMonth(), input.getYear());
    ui->startDate->setDate(d);
}
void TaskModal::setEndDate(project::Date input) {
    QDate d = QDate(input.getDate(), input.getMonth(), input.getYear());
    ui->endDate->setDate(d);
}
void TaskModal::setState(std::string input) {
    int index = ui->stateCombo->findText(QString::fromStdString(input));
    ui->stateCombo->setCurrentIndex(index);
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

void TaskModal::on_saveButton_clicked()
{
    qDebug() << "?";
    if(task == nullptr) {
        QDate start = ui->startDate->date();
        QDate end = ui->endDate->date();
        //Task(std::string i, std::string n, std::string d, Date* start, Date* end);
        task = new project::Task("new", ui->title->text().toStdString(), ui->description->toPlainText().toStdString(), project::Date(start.year(),start.month(),start.day()), project::Date(end.year(),end.month(),end.day()));
        task->setState(ui->stateCombo->currentText().toStdString());
    } else {
        task->setName(ui->title->text().toStdString());
        QDate start = ui->startDate->date();
        task->setStartDate(project::Date(start.year(),start.month(),start.day()));
        QDate end = ui->endDate->date();
        task->setEndDate(project::Date(end.year(),end.month(),end.day()));
        task->setState(ui->stateCombo->currentText().toStdString());
        task->setDescription(ui->description->toPlainText().toStdString());
    }

    qobject_cast<MainWindow*>(this->parent())->SaveTask(task);
}

