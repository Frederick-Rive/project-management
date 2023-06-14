#include "login.h"
#include "ui_login.h"
#include <QWidget>
#include <QPushButton>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();
}

login::~login()
{
    delete ui;
}

void login::ReplyFinished(QNetworkReply *reply) {
    qDebug() << reply->read(9999);
}

void login::on_loginButton_clicked()
{
    if(ui->usernameEdit->text() != "" && ui->passwordEdit->text() != "") {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        qDebug() << "WE ARE SO DONE";

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::ReplyFinished);
        qDebug() << "Connection status:" << status;

        manager->get(QNetworkRequest(QUrl("http://localhost:6069/account?u=" + username + "&h=" + password)));
    }
}


void login::on_registerButton_clicked()
{
    if(ui->usernameEdit->text() != "" && ui->passwordEdit->text() != "") {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        qDebug() << "WE ARE SO DONE";

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::ReplyFinished);
        qDebug() << "Connection status:" << status;

        QHttpPart loginPart;
        loginPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("form-data; name=\"u\""));
        loginPart.setBody(username.toUtf8());

        QHttpPart hashPart;
        hashPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("form-data; name=\"h\""));
        hashPart.setBody(password.toUtf8());

        QHttpMultiPart *fullPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        qDebug() << &fullPart;

        manager->post(QNetworkRequest(QUrl("http://localhost:6069/account")), fullPart);
    }
}

