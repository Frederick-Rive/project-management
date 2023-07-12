#include "login.h"
#include "ui_login.h"
#include <QWidget>
#include <QPushButton>
#include <mainwindow.h>
#include <QProcess>
#include <QCryptographicHash>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    crypt = new SimpleCrypt(Q_UINT64_C(0x0c2ad4a4acb9f023));
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
    manager = new QNetworkAccessManager();
    if(ui->usernameEdit->text() != "" && ui->passwordEdit->text() != "") {
        QString username = ui->usernameEdit->text();
        QString password = ui->passwordEdit->text();

        QString uCipher = crypt->encryptToString(username);

        QCryptographicHash hashAlgo = QCryptographicHash(QCryptographicHash::Md5);

        QString pHash = hashAlgo.hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::LoginFinished);
        qDebug() << "Connection status:" << status;

        manager->get(QNetworkRequest(QUrl("http://localhost:6069/account?u=" + uCipher + "&h=" + pHash)));
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

        QString uCipher = crypt->encryptToString(username);

        QCryptographicHash hashAlgo = QCryptographicHash(QCryptographicHash::Md5);

        QString pHash = hashAlgo.hash(password.toUtf8(), QCryptographicHash::Md5).toHex();

        QByteArray data = QByteArray(("{ \"n\":\""+uCipher+"\",\"h\":\""+pHash+"\" }").toUtf8());

        QNetworkRequest request = QNetworkRequest(QUrl("http://localhost:6069/account"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

        auto status = connect(manager, &QNetworkAccessManager::finished,
                          this, &login::RegisterFinished);

        manager->post(request, data);
        qDebug() << "Connection status:" << status;
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

