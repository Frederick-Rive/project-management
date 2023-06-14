#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>

namespace Ui {
class Notification;
}

class Notification : public QWidget
{
    Q_OBJECT

public:
    explicit Notification(QString title, QWidget *parent = nullptr);
    ~Notification();

private:
    Ui::Notification *ui;
};

#endif // NOTIFICATION_H
