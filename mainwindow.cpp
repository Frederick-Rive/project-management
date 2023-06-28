#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notification.h"
#include "kanbanboard.h"
#include "ganttchart.h"
#include "adminscreen.h"
#include <QMouseEvent>
#include <QSize>
#include "login.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //project temp

    project::Project *tempProject = new project::Project("Create Application", new project::Date(30, 4, 2023), new project::Date(30, 5, 2023));
    project::Account *tempAccount = new project::Account("Freddie", "psword", "freddierive@gmail.com");
    project::UserAccess *tempUA = new project::UserAccess(tempAccount, "Admin");

    this->setStyleSheet(
                "* { background-color: #fff }"
                "QWidget#leftWidget { background-color: #E7ECEF; }"
                "QWidget#headerWidget { background-color: #E7ECEF; }"
                "QPushButton { background-color: #6096BA; border: none; color: #fff }"
                "QPushButton:hover { background-color: #5096aA; border: none; color: #fff }"
                );

    QWidget *pfpWidget = new QWidget(this);
    ui->leftLayout->addWidget(pfpWidget);

    usernameLabel = new QLabel(this);
    usernameLabel->setText(QString::fromStdString(tempUA->getUsername()));
    ui->leftLayout->addWidget(usernameLabel);

    QLabel *projectTitle = new QLabel(this);
    projectTitle->setText("Project");
    ui->leftLayout->addWidget(projectTitle);
    projectName = new QLabel(this);
    projectName->setText(QString::fromStdString(tempProject->getName()));
    ui->leftLayout->addWidget(projectName);

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
    connect(logOut, SIGNAL(QPushButton::clicked), this, SLOT(MainWindow::Logout));

    //mainwindow

    mainWidget = new KanbanBoard(this);
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
        qDebug() << r;
        QString field = r.split(":")[0].replace("\"", "");
        QString value = r.split(":")[1].replace("\"", "");
        qDebug() << field << ": " << value;
        if (field == "username") {
            username = value.toStdString();
        } else if (field == "password") {
            password = value.toStdString();
        } else if (field == "_id") {
            id = value.toStdString();
        }
    }
    user = new project::Account(username, password, id);
    usernameLabel->setText(QString::fromStdString(user->getUsername()));

    GetTask("6496eaea0cb82235725b3c38");
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

    std::string id, name, description;
    project::Date *start, *end;
    QStringList record = answer.split("|");

    for (QString r : record) {
        qDebug() << r;
        QString field = r.split(":")[0].replace("\"", "");
        QString value = r.split(":")[1].replace("\"", "");
        qDebug() << field << ": " << value;
        if (field == "_id") {
            id = value.toStdString();
        } else if (field == "name") {
            name = value.toStdString();
        } else if (field == "description") {
            description = value.toStdString();
        } else if (field == "startDate") {
            QStringList nums = value.split(',');
            start = new project::Date(nums[0].toInt(),nums[1].toInt(),nums[2].toInt());
        } else if (field == "endDate") {
            QStringList nums = value.split(',');
            end = new project::Date(nums[0].toInt(),nums[1].toInt(),nums[2].toInt());
        }
    }

    project::Task *t = new project::Task(id, name, description, start, end);
}

void MainWindow::on_kanbanButton_clicked()
{
    if (activeButton != ui->kanbanButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->kanbanButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new KanbanBoard(this, this);

    ui->mainLayout->addWidget(mainWidget);
}

void MainWindow::on_ganttButton_clicked()
{
    if (activeButton != ui->ganttButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->ganttButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new GanttChart();

    ui->mainLayout->addWidget(mainWidget);
}

void MainWindow::on_adminButton_clicked()
{
    if (activeButton != ui->adminButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->adminButton;
    activeButton->setStyleSheet("background-color: #274C77;");

    mainWidget = new AdminScreen();

    ui->mainLayout->addWidget(mainWidget);
}

void MainWindow::on_closeButton_clicked()
{
    this->close();
}

void MainWindow::on_minimiseButton_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::ClearMainWidget() {
    delete mainWidget;
}

void MainWindow::OpenTaskModal(project::Task *task) {
    modal = new TaskModal(task, this);
    modal->move(ui->mainLayout->geometry().center() - modal->geometry().center());
    modal->show();
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

