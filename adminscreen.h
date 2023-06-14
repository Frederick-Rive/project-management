#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include <QWidget>

namespace Ui {
class AdminScreen;
}

class AdminScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AdminScreen(QWidget *parent = nullptr);
    ~AdminScreen();

private:
    Ui::AdminScreen *ui;
};

#endif // ADMINSCREEN_H
