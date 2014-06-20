#include <QApplication>

#include "connection.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    MainWindow m;
    m.show();
    if (!createConnection())
        return 1;

    return a.exec();
}
