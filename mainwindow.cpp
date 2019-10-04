#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);
    QCalendarWidget * pCW = new QCalendarWidget(this);
    pCW->setFirstDayOfWeek( Qt::Monday );
    ui->dateEdit->setCalendarWidget( pCW );

    modelMar=new QSqlQueryModel(this);
    modelDiam=new QSqlQueryModel(this);
    modelNam=new QSqlQueryModel(this);
    modelOTK=new QSqlQueryModel(this);

    updModels();

    ui->boxMarka->setModel(modelMar);
    ui->boxMarka->setModelColumn(1);
    ui->boxDiam->setModel(modelDiam);
    ui->boxDiam->setModelColumn(1); 
    ui->boxNam->setModel(modelNam);
    ui->boxNam->setModelColumn(1);
    //ui->boxOTK->setModel(modelOTK);
    //ui->boxOTK->setModelColumn(1);

    connect(ui->cmdPrint,SIGNAL(clicked()),this,SLOT(genLabel()));
    connect(ui->cmdUpd,SIGNAL(clicked(bool)),this,SLOT(updModels()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::genLabel()
{
    QString str;
    str+=tr("Марка - ");
    str+=ui->boxMarka->currentText();
    str+="\n";
    str+=tr("Диаметр, мм - ");
    str+=ui->boxDiam->currentText();
    str+="\n";
    str+=tr("Плавка - ");
    str+=ui->editPlav->text();
    str+="\n";
    str+=tr("Партия - ");
    str+=ui->editPart->text();
    str+="\n";
    str+=tr("Волоч. - ");
    //str+=ui->boxNam->model()->data(ui->boxNam->model()->index(ui->boxNam->currentIndex(),2),Qt::EditRole).toString();
    str+=ui->boxNam->currentText();
    str+="\n";
    //str+=tr("ОТК - ");
    //str+=ui->boxOTK->currentText();
    //str+="\n";
    str+=tr("Дата - ");
    str+=ui->dateEdit->date().toString("dd.MM.yy");
    str+="\n";
    str+=tr("Масса нетто, кг - ");
    str+=ui->editMas->text();
    LblEngine e;
    e.createLblEd(str,QString());
}

void MainWindow::updModels()
{
    setQueryModel("select id, nam from provol where is_w=1 order by nam",modelMar);
    setQueryModel("select id, sdim from diam order by sdim",modelDiam);
    setQueryModel("select r.id, r.first_name||' '||substr(r.last_name,1,2)||'. '||substr(r.middle_name,1,1)||'. '||'('||n.num||')' as rab, n.num "
                       "from wire_namoch as n "
                       "inner join wire_empl as r on n.id_rab = r.id "
                       "where r.id <> 0 and n.id_pr = 2 "
                       "order by rab",modelNam);
    setQueryModel("select id, nam from otk order by nam",modelOTK);
}

void MainWindow::setQueryModel(QString query, QSqlQueryModel *model)
{
    model->setQuery(query);
    if (model->lastError().isValid()){
        QMessageBox::critical(this,tr("Ошибка"),model->lastError().text(),QMessageBox::Ok);
    }
}
