#include <QtGui>
#include "mainwindow.h"
#include "pgdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PgDialog d(QObject::tr("Печать этикеток"));
        if (d.exec()!=QDialog::Accepted) exit(1);
    MainWindow w;
    w.show();
    return a.exec();
}
