#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QHttpMultiPart>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    void ReplyFinished(QNetworkReply *reply);
    void logIn();

private slots:
    void on_loginButton_clicked();
private:
    Ui::login *ui;

    QNetworkAccessManager *manager;
    QNetworkRequest request;
};
#endif // LOGIN_H
