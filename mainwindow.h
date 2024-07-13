#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addObjectsToList();
private slots:
    void on_addMonster_clicked();
    void on_removeMonster_clicked();

    void on_loadDbButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB_Connection;

};
#endif // MAINWINDOW_H
