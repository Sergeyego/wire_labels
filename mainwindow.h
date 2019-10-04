#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QCalendarWidget>
#include "lblengine.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *modelMar;
    QSqlQueryModel *modelDiam;
    QSqlQueryModel *modelNam;
    QSqlQueryModel *modelOTK;
    void setQueryModel(QString query, QSqlQueryModel *model);
private slots:
    void genLabel();
    void updModels();
};

#endif // MAINWINDOW_H
