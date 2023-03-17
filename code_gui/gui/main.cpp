#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;

    //open qss file
//    QFile file("/Medize.qss");
//    file.open(QFile::ReadOnly);

//    QString styleSheet { QLatin1String(file.readAll()) };

//    //setup stylesheet
//    app.setStyleSheet(styleSheet);

    w.show();
    return app.exec();
}
