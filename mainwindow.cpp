#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSqlError>
#include <QTableView>
#include "sql_code.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  path = QFileDialog::getOpenFileName(this,"Open file", "", "Database (*db)");
    db = QSqlDatabase::addDatabase("QSQLITE"); //подключаем драйвер для sqlite
    db.setDatabaseName(path); //открываем базу по умолчанию

    if(!db.open()){ //если не открылось выводим причину ошибки
        qDebug()<< db.lastError().text();
        return;
    }
    else {
        qDebug()<<"Complete\n";
    }

    QString table_name = db.tables()[0];


    model = new QSqlTableModel(this, db); //запускаем нашу таблицу и показываем ее через внутриний класс таблиц
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //OnFieldChange по-умолчанию
    model->setTable(table_name); //выбираем таблицу в базе
    model->select();//делаем выборку всей таблицы
    ui->tableView->setModel(model);

    sort_model = new QSqlTableModel(this, db);
    sort_model->setEditStrategy(QSqlTableModel::OnManualSubmit); //OnFieldChange по-умолчанию
    sort_model->setTable(table_name); //выбираем таблицу в базе
    sort_model->select();//делаем выборку всей таблицы
    ui->tableView_2->setModel(sort_model);

        ui->comboBox->clear();
        for(QString &table_name:db.tables())
            ui->comboBox->addItem(table_name);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_row_box_clicked()
{
    qDebug()<<"inserting row"<< model->insertRow(model->rowCount());
}

void MainWindow::on_reselect_box_clicked()
{
    db.close();
    if(!db.open()){ //если не открылось выводим причину ошибки
        qDebug()<< db.lastError().text();
        return;
    }
    else {
        qDebug()<<"Complete\n";
    }
    model->select();
    sort_model->select();
}

void MainWindow::on_revert_box_clicked()
{
    model->revertAll(); //отменить изменения
    qDebug()<<"reverting model";
}

void MainWindow::on_delete_row_box_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
              if(selectedRow>=0){
               qDebug()<<"deleting row:"<<model->removeRow(selectedRow);
}
              else{
              qDebug()<<"no row selected";
}
}

void MainWindow::on_submit_box_clicked()
{
    model->submitAll();  //подтвердить изменения и внести их в БД    
    qDebug()<<"submiting model";

}


void MainWindow::on_dialog_search_clicked()
{
    QString arg = ui->lineEdit->text();
    sort_model->setFilter(arg);
    sort_model->select();
}

void MainWindow::on_request_clicked()
{
   SQL_code* wnd = new SQL_code(this);
   wnd->show();

   connect(wnd, SIGNAL(Selection(QString)), this, SLOT(makerequest(QString)));
}

void MainWindow::makerequest(const QString &req)
{
    query = new QSqlQuery(db);
    if(query->exec(req))
    model->select();
    else {
    qDebug()<< query->lastError().text();
    }
}

void MainWindow::on_pushButton_clicked()
{
    path = QFileDialog::getOpenFileName(this,"Open file", "", "Database (*db)");

    db.setDatabaseName(path); //открываем базу по умолчанию


    if(!db.open()){ //если не открылось выводим причину ошибки
        qDebug()<< db.lastError().text();
        return;
    }
    else {
        qDebug()<<"Complete\n";
    }
    ui->comboBox->clear();
    for(QString &table_name:db.tables())
        ui->comboBox->addItem(table_name);


    model = new QSqlTableModel(this, db); //запускаем нашу таблицу и показываем ее через внутриний класс таблиц
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //OnFieldChange по-умолчанию
    model->setTable(ui->comboBox->currentText()); //выбираем таблицу в базе
    model->select();//делаем выборку всей таблицы
    ui->tableView->setModel(model);

    sort_model = new QSqlTableModel(this, db);
    sort_model->setEditStrategy(QSqlTableModel::OnManualSubmit); //OnFieldChange по-умолчанию
    sort_model->setTable(ui->comboBox->currentText()); //выбираем таблицу в базе
    sort_model->select();//делаем выборку всей таблицы
    ui->tableView_2->setModel(sort_model);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    model->setTable(arg1); //выбираем таблицу в базе
    model->select();//делаем выборку всей таблицы
    ui->tableView->setModel(model);

    sort_model->setTable(arg1); //выбираем таблицу в базе
    sort_model->select();//делаем выборку всей таблицы
    ui->tableView_2->setModel(sort_model);
}


void MainWindow::on_Boutton_clear_clicked()
{
     ui->lineEdit->clear();
}
