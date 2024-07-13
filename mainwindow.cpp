#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "monsterobj.h"
#include <vector>
#include <QVariant>
#include <iostream>

using namespace std;
// Global Variable Store:
double crLevel = 0;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addObjectsToList(); //called on creation.


    DB_Connection = QSqlDatabase::addDatabase("QSQLITE"); //setting up sqlite database connection
    DB_Connection.setDatabaseName("C:\\Users\\Connor\\Desktop\\coding 2024\\C++\\qt stuff\\CRBattle\\test1.db"); //selecting db
    if(DB_Connection.open()){
        qDebug() << "Database is connected";
    } else{
        qDebug() <<"Database is not working!!!!!";
        qDebug() <<"Error: " << DB_Connection.lastError();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addObjectsToList(){ //we need to add monsters to our list so lets do that.
    for(int i = 0; i < 2; i++){ // iteration logic will need to be changed as system improves, espically with database addtion.
    MonsterObj monsterStart; //creates inital object
    MonsterObj monster = monsterStart.createMonsters(i); //calls a function to return monster objects
    QListWidgetItem* item = new QListWidgetItem();
    QVariant convertVector;
    convertVector.setValue(monster.abilitys); //vectors can't be used by qt, so we have to convert to QVariants.
    item->setText(monster.name);
    item->setData(Qt::UserRole, monster.type);
    item->setData(Qt::UserRole + 1, monster.cr);
    item->setData(Qt::UserRole + 2, convertVector);
    item->setData(Qt::ToolTipRole, monster.description);
    ui->monsterList->addItem(item); //adds monster to list
    }
}


void MainWindow::on_addMonster_clicked()
{
    auto selectedMonster = ui->monsterList->selectedItems();
    for(auto monster:selectedMonster){
        ui->combatList->addItem(monster->clone()); //copys full list object
        crLevel += monster->data(Qt::UserRole+1).toDouble(); // add the toDouble because Doubles are auto converted for some reason????
        ui->crTotal->setText(QString::number(crLevel));
    }
}


void MainWindow::on_removeMonster_clicked()
{
    crLevel -= ui->combatList->currentItem()->data(Qt::UserRole+1).toDouble();
    ui->crTotal->setText(QString::number(crLevel));
    ui->combatList->takeItem(ui->combatList->currentRow());
}


void MainWindow::on_loadDbButton_clicked()
{
    DB_Connection.open();
    QString data;
    QSqlQuery QueryLoadData;
    QueryLoadData.exec("SELECT name FROM monster where type = 'Goblinoid';");

    if( !QueryLoadData.exec("SELECT name FROM monster where type = 'Goblinoid';") ) {
        qDebug() << "Error:" << QueryLoadData.lastError().text();                       // Error check for DB
    }

    //QStringList Tables = DB_Connection.tables(); //displays tables in db to console
    //qDebug() << Tables;
    //if(QueryLoadData.exec()){
    qDebug() << "pre loop check";
    while (QueryLoadData.next()) {
        QString name = QueryLoadData.value(0).toString();
        data = name;
        qDebug() << "Name: " << name;
    }
    //} else {qDebug() << "Why the fuck isn't this working";}

    ui->dbTestLabel->setText(data);



    QueryLoadData.exec("SELECT * FROM monster;");
    while(QueryLoadData.next()){
        MonsterObj monster;
        monster.name = QueryLoadData.value(0).toString();
        monster.type = QueryLoadData.value(1).toString();
        monster.cr = QueryLoadData.value(2).toDouble();
        monster.description = QueryLoadData.value(4).toString();

        qDebug() << monster.description;

         QListWidgetItem* item = new QListWidgetItem();
        item->setText(monster.name);
        item->setData(Qt::UserRole, monster.type);
        item->setData(Qt::UserRole + 1, monster.cr);
        item->setData(Qt::ToolTipRole, monster.description);
        ui->monsterList->addItem(item); //adds monster to list
    }





}

