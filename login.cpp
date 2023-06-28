#include "login.h"
#include "ui_login.h"
#include <QWidget>
#include <QPushButton>
#include <mainwindow.h>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::ReplyFinished(QNetworkReply *reply) {
    auto read = reply->read(1);
    std::string result = std::string(read.constData(), 1);
    if (std::string(read.constData(), 1) == "1") {
        logIn();
    }
    reply->abort();
    reply->deleteLater();
    reply->manager()->deleteLater();
}

void login::on_loginButton_clicked()
{
    manager = new QNetworkAccessManager();
    if(ui->usernameEdit->text() != "" && ui->passwordEdit->text() != "") {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::ReplyFinished);
        qDebug() << "Connection status:" << status;

        manager->get(QNetworkRequest(QUrl("http://localhost:6069/account?u=" + username + "&h=" + password)));
    }
}



void login::logIn() {
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}

