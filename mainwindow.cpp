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

    // Style sheet for the main widget
    // #6096BA - button colour
    // #E7ECEF - background
    this->setStyleSheet(
                "* { background-color: #fff }"
                "QLabel { background-color: #E7ECEF; padding: 5px; font-size: 18px; text-align: centre; }"
                "QWidget#leftWidget { background-color: #E7ECEF; }"
                "QWidget#headerWidget { background-color: #E7ECEF; }"
                "QPushButton { background-color: #6096BA; border: none; color: #fff }"
                "QPushButton:hover { background-color: #5096aA; border: none; color: #fff }"
                );

    // Init profile picture (using default for now)
    QLabel *pfpWidget = new QLabel(this);
    QPixmap pfp = QPixmap(":/images/images/user_icon.png", "PNG");
    pfpWidget->setPixmap(QPixmap(":/images/images/user_icon.png", "PNG"));
    pfpWidget->setStyleSheet("margin: 0px auto;");
    ui->leftLayout->addWidget(pfpWidget);

    // Init username text label (username is set later)
    usernameLabel = new QLabel(this);
    ui->leftLayout->addWidget(usernameLabel);

    // Init project title (placeholder)
    QLabel *projectTitle = new QLabel(this);
    projectTitle->setText("<Project Name>");
    ui->leftLayout->addWidget(projectTitle);

    // Init Notification widgets (placeholder)
    Notification *overdueNotif = new Notification("Overdue", this);
    ui->leftLayout->addWidget(overdueNotif);
    Notification *dueSoonNotif = new Notification("Due Soon", this);
    ui->leftLayout->addWidget(dueSoonNotif);
    Notification *startingSoonNotif = new Notification("Starting Soon", this);
    ui->leftLayout->addWidget(startingSoonNotif);
    ui->leftLayout->addStretch();

    // Init logout button
    QPushButton *logOut = new QPushButton(this);
    logOut->setText("Log Out");
    ui->leftLayout->addWidget(logOut);
    connect(logOut, &QPushButton::clicked, this, &MainWindow::Logout);

    // mainWidget is the widget in the main section of the window. It will either be a Kanban board, gantt chart, or admin screen
    // On launch, it is set to KanbanBoard
    mainWidget = new KanbanBoard(this);;
    ui->mainLayout->addWidget(mainWidget);
    activeButton = ui->kanbanButton;
    activeButton->setStyleSheet("background-color: #274C77;");

    // Remove window frame
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // Move window to centre of screen
    move(screen()->geometry().center() - frameGeometry().center());

    // Get user data from the database
    GetUser();

    // Event filters allow users to drag the window by dragging on the header / left bar
    ui->headerWidget->installEventFilter(this);
    ui->leftWidget->installEventFilter(this);

    // Init encryption object
    crypt = new SimpleCrypt(Q_UINT64_C(0x0c2ad4a4acb9f023));

    // Gets all tasks associated with the user
    GetUserTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Sends HTTP Get request to get User object
void MainWindow::GetUser() {
    manager = new QNetworkAccessManager;
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::UserReply);

    manager->get(QNetworkRequest(QUrl("http://localhost:6069/user")));
}

// Upon recieving account reply from backend, parse JSON and create Account object to store the data
void MainWindow::UserReply(QNetworkReply *reply) {
    QString answer = reply->readAll();

    std::string username, password, email, id;
    std::vector<std::string> projects;
    // JSON is changed in the JS script to replace commas with pipes, to make it easier to parse here
    QStringList record = answer.split("|");
    for (QString r : record) {
        QString field = r.split(":")[0].replace("\"", "");
        QString value = r.split(":")[1].replace("\"", "");

        // Clunky, will likely break if any data that isnt the exact JSON object its designed for is passed in
        if (field == "username") {
            // Username needs to be decrypted
            username = crypt->decryptToString(value).toStdString();
        } else if (field == "password") {
            password = value.toStdString();
        } else if (field == "_id") {
            id = value.toStdString();
        }
    }
    user = new project::Account(id, username, password, "none");

    // Assign Username text
    usernameLabel->setText(QString::fromStdString(user->getUsername()));
}

// Sends a HTTP Get request to the backend for the IDS of all tasks associated with the current user
void MainWindow::GetUserTasks() {
    // Wipe current tasks
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

// Upon recieving UserTask reply from backend, parse list of ID's and query backend for each ID
void MainWindow::UserTaskReply(QNetworkReply *reply) {
    QString answer = reply->readAll();
    if (answer == "0") {
        // return if there are no tasks
        return;
    }
    QStringList ids = answer.split('|');
    for(QString id : ids) {
        GetTask(id);
    }
}


// Query backend for task, based on ID
void MainWindow::GetTask(QString id) {
    manager = new QNetworkAccessManager;
    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::TaskReply);

    manager->get(QNetworkRequest(QUrl("http://localhost:6069/task?id="+id)));
}

// Upon recieving Task reply from backend, parse JSON from backend, create Task object to store the data, and create a widget to display the task on the Kanban board
void MainWindow::TaskReply(QNetworkReply *reply) {
    QString answer = reply->readAll();
    qDebug() << answer;

    std::string id, name, description, state;
    project::Date start = project::Date(0,0,0), end = project::Date(0,0,0);
    // JSON is changed in the JS script to replace commas with pipes, to make it easier to parse here
    QStringList record = answer.split("|");

    for (QString r : record) {
        QString field = r.split(":")[0].replace("\"", "");
        QString value = r.split(":")[1].replace("\"", "");

        // Multiple fields need to be decrypted
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

    // Send task to list based on its state
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

// Send latest task in an array
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

// Switch active window to Kanban Board (disabled)
void MainWindow::on_kanbanButton_clicked() {
    /*if (activeButton != ui->kanbanButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->kanbanButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new KanbanBoard(this, this);

    ui->mainLayout->addWidget(mainWidget);*/
}

// Switch active window to Gantt Chart (disabled)
void MainWindow::on_ganttButton_clicked() {
    /*if (activeButton != ui->ganttButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->ganttButton;
    activeButton->setStyleSheet("background-color: #274C77;");
    mainWidget = new GanttChart();

    ui->mainLayout->addWidget(mainWidget);*/
}

// Switch active window to Admin Screen (disabled)
void MainWindow::on_adminButton_clicked() {
    /*if (activeButton != ui->adminButton) {
        activeButton->setStyleSheet("background-color: #6096BA;");
    }

    ClearMainWidget();

    activeButton = ui->adminButton;
    activeButton->setStyleSheet("background-color: #274C77;");

    mainWidget = new AdminScreen();

    ui->mainLayout->addWidget(mainWidget);*/
}

// Close Application
void MainWindow::on_closeButton_clicked() {
    this->close();
}

// Minimise Application
void MainWindow::on_minimiseButton_clicked() {
    this->setWindowState(Qt::WindowMinimized);
}

// Handles deleting the main widget
void MainWindow::ClearMainWidget() {
    delete mainWidget;
}

// Opens the task modal with values assinged to a task.
void MainWindow::OpenTaskModal(project::Task *task) {
    modal = new TaskModal(task, this);
    modal->move(mainWidget->mapToGlobal(mainWidget->geometry().topLeft()) - frameGeometry().topLeft());
    modal->show();
}

// Send HTTP Post request to upload task to the database
void MainWindow::SaveTask(project::Task *task) {
    // Assign current user access to the task
    task->addUser(user->getID());

    manager = new QNetworkAccessManager();

    // Convert dates to array string
    QString start, end, users = "[";
    QTextStream(&start) << "["<<task->getStartDate().getDate()<<","<<task->getStartDate().getMonth()<<","<<task->getStartDate().getYear()<<"]";
    QTextStream(&end) << "["<<task->getEndDate().getDate()<<","<<task->getEndDate().getMonth()<<","<<task->getEndDate().getYear()<<"]";

    // Assign users to array string
    for (int i = 0; i < task->getUserCount(); i++) {
        users += "\"" + QString::fromStdString(task->getUser(i)) + (i != task->getUserCount() - 1 ? "\",": "\"");
    }
    users += "]";

    // Create QByteArray as string from Task data
    QByteArray data = QByteArray(("{ \"n\":\""+crypt->encryptToString(QString::fromStdString(task->getName()))+"\",\"d\":\""+crypt->encryptToString(QString::fromStdString(task->getDescription()))+"\",\"s\":\""+crypt->encryptToString(QString::fromStdString(task->getState()))+"\","
                                    "\"sd\":"+start+",\"ed\":"+end+",\"u\": "+users+" }").toUtf8());

    // Setup request options
    QNetworkRequest request = QNetworkRequest(QUrl("http://localhost:6069/task"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    auto status = connect(manager, &QNetworkAccessManager::finished,
                      this, &MainWindow::TaskSaved);
    manager->post(request, data);
    qDebug() << "Connection status:" << status;
}

// Once task is saved, add new task to the Kanban Board
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

// Logout
void MainWindow::Logout() {
    login *l = new login();
    l->show();
    this->close();
}

// Handles dragging the application around the screen
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

// Handles deleting modal when the user clicks off of it
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

