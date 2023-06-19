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
    void GetUser() const;
    void UserReply(QNetworkReply *reply);
    void GetProject() const;
    void ProjectReply(QNetworkReply *reply);
    void GetTask() const;
    void TaskReply(QNetworkReply *reply);

    void login(QString please);

private slots:
    void on_adminButton_clicked();

    void on_ganttButton_clicked();

    void on_kanbanButton_clicked();

    bool eventFilter (QObject *obj, QEvent *event);

    void on_closeButton_clicked();

    void on_minimiseButton_clicked();

    //void ReplyFin(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    QWidget *mainWidget;
    QPushButton *activeButton = nullptr;
    QPoint startPos;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    QLabel *usernameLabel, *projectName;

    project::Account *user;

};

#endif // MAINWINDOW_H
