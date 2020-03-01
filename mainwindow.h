#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:    

    void on_add_row_box_clicked();

    void on_reselect_box_clicked();

    void on_revert_box_clicked();

    void on_delete_row_box_clicked();

    void on_submit_box_clicked();

    void on_dialog_search_clicked();

    void on_request_clicked();

    void makerequest (const QString &filepath);

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Boutton_clear_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    QSqlTableModel* sort_model;
    QSqlQuery* query;
    QString path;

};
#endif // MAINWINDOW_H
