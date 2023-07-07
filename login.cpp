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

void login::LoginFinished(QNetworkReply *reply) {
    auto read = reply->read(1);
    std::string result = std::string(read.constData(), 1);
    if (std::string(read.constData(), 1) == "1") {
        LogIn();
    }
    reply->manager()->deleteLater();
}

void login::on_loginButton_clicked()
{
//    QString username = ui->usernameEdit->text();

//    std::string cipher = crypt::encrypt(username.toStdString());
//    qDebug() << QString::fromStdString(cipher);
//    qDebug() << QString::fromStdString(crypt::decrypt(cipher));

    manager = new QNetworkAccessManager();
    if(ui->usernameEdit->text() != "" && ui->passwordEdit->text() != "") {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::LoginFinished);
        qDebug() << "Connection status:" << status;

        manager->get(QNetworkRequest(QUrl("http://localhost:6069/account?u=" + username + "&h=" + password)));
    }
}



void login::LogIn() {
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}

void login::on_registerButton_clicked()
{
    manager = new QNetworkAccessManager();
    if(ui->usernameEdit->text() != "" && ui->passwordEdit->text() != "") {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();
        QByteArray data = QByteArray(("{ \"n\":\""+username+"\",\"h\":\""+password+"\" }").toUtf8());
        //QByteArray *data = new QByteArray("username="+username+"&password="+password+"&if_login=Y&B2=%B5%C7%C2%BC%28Login%29");

        qDebug() << data;

        QNetworkRequest request = QNetworkRequest(QUrl("http://localhost:6069/account"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::RegisterFinished);

        manager->post(request, data);
        qDebug() << "Connection status:" << status;
        //reply->readyRead();
        //manager->post(QNetworkRequest(QUrl("http://localhost:6069/account?u=" + username + "&h=" + password)));
    }
}

void login::RegisterFinished(QNetworkReply *reply) {
    //QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    auto read = reply->read(1);
    std::string result = std::string(read.constData(), 1);
    if (std::string(read.constData(), 1) == "1") {
        LogIn();
    }
    reply->manager()->deleteLater();
}

