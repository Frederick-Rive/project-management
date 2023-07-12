#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notification.h"
#include <QMouseEvent>
#include <QSize>
#include "login.h"
#include "kanbanboard.h"
#include "ganttchart.h"
#include "adminscreen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //project temp

    project::Project *tempProject = new project::Project("Create Application", new project::Date(30, 4, 2023), new project::Date(30, 5, 2023));

    this->setStyleSheet(
                "* { background-color: #fff }"
                "QLabel { background-color: #E7ECEF; padding: 5px; font-size: 18px; text-align: centre; }"
                "QWidget#leftWidget { background-color: #E7ECEF; }"
                "QWidget#headerWidget { background-color: #E7ECEF; }"
                "QPushButton { background-color: #6096BA; border: none; color: #fff }"
                "QPushButton:hover { background-color: #5096aA; border: none; color: #fff }"
                );

    QLabel *pfpWidget = new QLabel(this);
    QPixmap pfp = QPixmap(":/images/images/user_icon.png", "PNG");
    //pfp.scaled(100, 100);
    pfpWidget->setPixmap(QPixmap(":/images/images/user_icon.png", "PNG"));
    pfpWidget->setStyleSheet("margin: 0px auto;");
    ui->leftLayout->addWidget(pfpWidget);

    usernameLabel = new QLabel(this);
    ui->leftLayout->addWidget(usernameLabel);

    QLabel *projectTitle = new QLabel(this);
    projectTitle->setText("<Project Name>");
    ui->leftLayout->addWidget(projectTitle);
    //projectName = new QLabel(this);
    //projectName->setText(QString::fromStdString(tempProject->getName()));
    //ui->leftLayout->addWidget(projectName);

    Notification *overdueNotif = new Notification("Overdue", this);
    ui->leftLayout->addWidget(overdueNotif);
    Notification *dueSoonNotif = new Notification("Due Soon", this);
    ui->leftLayout->addWidget(dueSoonNotif);
    Notification *startingSoonNotif = new Notification("Starting Soon", this);
    ui->leftLayout->addWidget(startingSoonNotif);
    ui->leftLayout->addStretch();
    QPushButton *logOut = new QPushButton(this);
    logOut->setText("Log Out");
    ui->leftLayout->addWidget(logOut);
    connect(logOut, &QPushButton::clicked, this, &MainWindow::Logout);

    //mainwindow

    mainWidget = new KanbanBoard(this);;
    ui->mainLayout->addWidget(mainWidget);
    activeButton = ui->kanbanButton;
    activeButton->setStyleSheet("background-color: #274C77;");

    //remove window frame

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //move window to centre of screen

    move(screen()->geometry().center() - frameGeometry().center());

    //node::Start

    GetUser();

    ui->headerWidget->installEventFilter(this);
    ui->leftWidget->installEventFilter(this);

    crypt = new SimpleCrypt(Q_UINT64_C(0x0c2ad4a4acb9f023));

    GetUserTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetUser() {
    manager = new QNetworkAccessManager;
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::UserReply);

    manager->get(QNetworkRequest(QUrl("http://localhost:6069/user")));
}

void MainWindow::UserReply(QNetworkReply *reply) {
    QString answer = reply->readAll();

    std::string username, password, email, id;
    std::vector<std::string> projects;
    QStringList record = answer.split("|");
    for (QString r : record) {

        QString field = r.split(":")[0].replace("\"", "");
        QString value = r.split(":")[1].replace("\"", "");

        if (field == "username") {
            username = crypt->decryptToString(value).toStdString();
        } else if (field == "password") {
            password = value.toStdString();
        } else if (field == "_id") {
            id = value.toStdString();
        }
    }
    user = new project::Account(id, username, password, "none");
    usernameLabel->setText(QString::fromStdString(user->getUsername()));

    //GetTask("6496eaea0cb82235725b3c38");
}

void MainWindow::GetUserTasks() {
    for(project::Task* task : todo) {
        delete task;
    }
    for(project::Task* task : inprogress) {
        delete task;
    }
    for(project::Task* task : completed) {
        delete task;
    }

    todo.clear();
    inprogress.clear();
    completed.clear();

    manager = new QNetworkAccessManager;
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::UserTaskReply);

    manager->get(QNetworkRequest(QUrl("http://localhost:6069/usertasks")));
}

void MainWindow::UserTaskReply(QNetworkReply *reply) {
    QString answer = reply->readAll();
    QStringList ids = answer.split('|');
    for(QString id : ids) {
        GetTask(id);
    }
}

void MainWindow::GetTask(QString id) {
    manager = new QNetworkAccessManager;
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::TaskReply);

    manager->get(QNetworkRequest(QUrl("http://localhost:6069/task?id="+id)));
}
void MainWindow::TaskReply(QNetworkReply *reply) {
    QString answer = reply->readAll();
    qDebug() << answer;

    std::string id, name, description, state;
    project::Date start = project::Date(0,0,0), end = project::Date(0,0,0);
    QStringList record = answer.split("|");

    for (QString r : record) {
        QString field = r.split(":")[0].replace("\"", "");
        QString value = r.split(":")[1].replace("\"", "");
        if (field == "_id") {
            id = value.toStdString();
        } else if (field == "name") {
            name = crypt->decryptToString(value).toStdString();
        } else if (field == "description") {
            description = crypt->decryptToString(value).toStdString();
        } else if (field == "startDate") {
            QStringList nums = value.split(',');
            start = project::Date(nums[0].toInt(),nums[1].toInt(),nums[2].toInt());
        } else if (field == "endDate") {
            QStringList nums = value.split(',');
            end = project::Date(nums[0].toInt(),nums[1].toInt(),nums[2].toInt());
        } else if (field == "state") {
            state = crypt->decryptToString(value).toStdString();
        }
    }

    project::Task *t = new project::Task(id, name, description, start, end);
    t->setState(state);
    if (state == "To Do") {
        todo.push_back(t);
        emit(taskAdded(0));
    } else if (state == "In Progress") {
        inprogress.push_back(t);
        emit(taskAdded(1));
    } else if (state == "Completed") {
        completed.push_back(t);
        emit(taskAdded(2));
    }
}

project::Task* MainWindow::GetLatestTask(int state) {
    switch(state){
    case (0):
        return todo[todo.size() - 1];
    case (1):
        return inprogress[inprogress.size() - 1];
    case (2):
        return completed[completed.size() - 1];
    default:
        return nullptr;
    }
}

void MainWindow::on_kanbanButton_clicked() {
    if (activeButton != ui->kanbanButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->kanbanButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new KanbanBoard(this, this);

    ui->mainLayout->addWidget(mainWidget);
}

void MainWindow::on_ganttButton_clicked() {
    if (activeButton != ui->ganttButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->ganttButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new GanttChart();

    ui->mainLayout->addWidget(mainWidget);
}

void MainWindow::on_adminButton_clicked() {
    if (activeButton != ui->adminButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->adminButton;
    activeButton->setStyleSheet("background-color: #274C77;");

    mainWidget = new AdminScreen();

    ui->mainLayout->addWidget(mainWidget);
}

void MainWindow::on_closeButton_clicked() {
    this->close();
}

void MainWindow::on_minimiseButton_clicked() {
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::ClearMainWidget() {
    delete mainWidget;
}

void MainWindow::OpenTaskModal(project::Task *task) {
    modal = new TaskModal(task, this);
    modal->move(mainWidget->mapToGlobal(mainWidget->geometry().topLeft()) - frameGeometry().topLeft());
    modal->show();
}

void MainWindow::SaveTask(project::Task *task) {
    task->addUser(user->getID());

    manager = new QNetworkAccessManager();
    QString start, end, users = "[";
    QTextStream(&start) << "["<<task->getStartDate().getDate()<<","<<task->getStartDate().getMonth()<<","<<task->getStartDate().getYear()<<"]";
    QTextStream(&end) << "["<<task->getEndDate().getDate()<<","<<task->getEndDate().getMonth()<<","<<task->getEndDate().getYear()<<"]";

    for (int i = 0; i < task->getUserCount(); i++) {
        users += "\"" + QString::fromStdString(task->getUser(i)) + (i != task->getUserCount() - 1 ? "\",": "\"");
    }
    users += "]";

    QByteArray data = QByteArray(("{ \"n\":\""+crypt->encryptToString(QString::fromStdString(task->getName()))+"\",\"d\":\""+crypt->encryptToString(QString::fromStdString(task->getDescription()))+"\",\"s\":\""+crypt->encryptToString(QString::fromStdString(task->getState()))+"\","
                                    "\"sd\":"+start+",\"ed\":"+end+",\"u\": "+users+" }").toUtf8());

    QNetworkRequest request = QNetworkRequest(QUrl("http://localhost:6069/task"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::TaskSaved);
    manager->post(request, data);
    qDebug() << "Connection status:" << status;
}

void MainWindow::TaskSaved(QNetworkReply *reply) {
    auto read = reply->read(1);
    std::string result = std::string(read.constData(), 1);
    if (result == "1") {
        if (activeButton != ui->kanbanButton) {
            activeButton->setStyleSheet("background-color: #6096BA;");
        }

        ClearMainWidget();

        activeButton = ui->kanbanButton;
        activeButton->setStyleSheet("background-color: #274C77;");
        mainWidget = new KanbanBoard(this, this);

        ui->mainLayout->addWidget(mainWidget);

        GetUserTasks();
    }
    reply->manager()->deleteLater();
}

void MainWindow::Logout() {
    login *l = new login();
    l->show();
    this->close();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (obj == (QObject*)ui->headerWidget || obj == (QObject*)ui->leftWidget)
        {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                startPos = (mouseEvent->globalPosition() - frameGeometry().topLeft()).toPoint();
                return false;
            }
        }
    } else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton)
        {
            move(mouseEvent->globalPosition().toPoint() - startPos);
            return false;
        }
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (modal != nullptr) {
            delete modal;
            modal = nullptr;
        }
    }
    return;
}

