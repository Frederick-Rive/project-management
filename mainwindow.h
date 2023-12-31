#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QLabel>
#include "projectobjects.h"
#include "taskmodal.h"
#include "simplecrypt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void ClearMainWidget();

    void GetUser();
    void UserReply(QNetworkReply *reply);
    void GetProject();
    void ProjectReply(QNetworkReply *reply);
    void GetTask(QString id = "");
    void TaskReply(QNetworkReply *reply);
    void GetUserTasks();
    void UserTaskReply(QNetworkReply *reply);

    void OpenTaskModal(project::Task *task);
    void SaveTask(project::Task *task);

    project::Task* GetLatestTask(int state);

private slots:
    void on_adminButton_clicked();

    void on_ganttButton_clicked();

    void on_kanbanButton_clicked();

    void on_closeButton_clicked();

    void on_minimiseButton_clicked();

    void Logout();

    //void ReplyFin(QNetworkReply *reply);

    void TaskSaved(QNetworkReply *reply);

signals:
    void taskAdded(int state);
    void tasksUpdated();

private:
    Ui::MainWindow *ui;

    QWidget *mainWidget;
    QPushButton *activeButton = nullptr;
    QPoint startPos;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    QLabel *usernameLabel, *projectName;

    project::Account *user;

    TaskModal *modal = nullptr;

    std::vector<project::Task*> todo, inprogress, completed;

    SimpleCrypt *crypt;

    bool eventFilter (QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
