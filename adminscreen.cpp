#include "adminscreen.h"
#include "ui_adminscreen.h"

AdminScreen::AdminScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminScreen)
{
    ui->setupUi(this);
}

AdminScreen::~AdminScreen()
{
    delete ui;
}
