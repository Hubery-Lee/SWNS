#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QWidget(parent),
//    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setWindowTitle("使用说明");
}

Help::~Help()
{
    delete ui;
}
