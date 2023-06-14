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
    void TestConnection() const;
    static void ReplyFinished(QNetworkReply *reply);

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

};

#endif // MAINWINDOW_H
