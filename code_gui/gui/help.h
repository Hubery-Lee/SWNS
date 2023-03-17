#ifndef HELP_H
#define HELP_H

#include <QWidget>
//#include <QDialog>

namespace Ui {
class Help;
}

class Help : public QWidget
//class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();

private:
    Ui::Help *ui;
};

#endif // HELP_H
