#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notification.h"
#include "kanbanboard.h"
#include "ganttchart.h"
#include "adminscreen.h"
#include <QLabel>
#include <QMouseEvent>

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

    QLabel *usernameLabel = new QLabel(this);
    usernameLabel->setText(QString::fromStdString(tempUA->getUsername()));
    ui->leftLayout->addWidget(usernameLabel);

    QLabel *projectTitle = new QLabel(this);
    projectTitle->setText("Project");
    ui->leftLayout->addWidget(projectTitle);
    QLabel *projectName = new QLabel(this);
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

    manager = new QNetworkAccessManager();

    TestConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestConnection() const {
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::ReplyFinished);
    qDebug() << "Connection status:" << status;

    manager->get(QNetworkRequest(QUrl("http://localhost:6069/account")));//?username=Test&password=test
}

void MainWindow::ReplyFinished(QNetworkReply *reply) {
    QString answer = reply->readAll();
    qDebug() << answer;
    //QApplication::quit();
}

void MainWindow::on_kanbanButton_clicked()
{
    if (activeButton != ui->kanbanButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->kanbanButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new KanbanBoard();

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

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == (QObject*)ui->headerWidget)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                startPos = (mouseEvent->globalPosition() - frameGeometry().topLeft()).toPoint();
                return false;
            }
        }
        else if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton)
            {
                move(mouseEvent->globalPosition().toPoint() - startPos);
                return false;
            }
        }
    }
    return false;
}
