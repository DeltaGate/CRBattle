#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "monsterobj.h"
#include <vector>
#include <QVariant>
#include <iostream>
#include <QVector>

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
    QSqlQuery QueryLoadData;
    QueryLoadData.exec("SELECT name FROM monster where type = 'Goblinoid';");

    if( !QueryLoadData.exec("SELECT name FROM monster where type = 'Goblinoid';") ) {
        qDebug() << "Error:" << QueryLoadData.lastError().text();
    }

    qDebug() << "pre loop check";

    ui->dbTestLabel->setText("Database functional");

    int countAbilitys = 0;
    int countLetters = 0;
    string heldDataForCutting;

    QueryLoadData.exec("SELECT * FROM monster;");
    while(QueryLoadData.next()){

        //begin with counting abilitys total
        auto abilitys = QueryLoadData.value(3).toString();
        countAbilitys = 0;
        for(QChar let:abilitys){
            countAbilitys += (let == ',');
            if(let == ','){
            }
        }

        MonsterObj monster;
        monster.name = QueryLoadData.value(0).toString();
        monster.type = QueryLoadData.value(1).toString();
        monster.cr = QueryLoadData.value(2).toDouble();
        monster.description = QueryLoadData.value(4).toString();
        //setting inital monster obj values


        QVector<QString> abilitysToVector;
        //Vector for type conversion

        if(countAbilitys == 0){
            abilitysToVector = {QueryLoadData.value(3).toString()};
            monster.abilitys = abilitysToVector;
        }else
            {
                heldDataForCutting = QueryLoadData.value(3).toString().toStdString();

                for(int i = 0; i < countAbilitys; i++){
                    abilitysToVector.append(QString::fromStdString(heldDataForCutting.substr(0, heldDataForCutting.find(','))));
                    heldDataForCutting.erase(0, heldDataForCutting.find(',')+1);
                }

                abilitysToVector.append(QString::fromStdString(heldDataForCutting));
                monster.abilitys = abilitysToVector;
        }
        // setting monster abilitys value


        qDebug() << "Name: " << monster.name;
        qDebug() << monster.description;
        qDebug() << countAbilitys;
        qDebug() << monster.abilitys;


         QListWidgetItem* item = new QListWidgetItem();
        item->setText(monster.name);
        item->setData(Qt::UserRole, monster.type);
        item->setData(Qt::UserRole + 1, monster.cr);
        item->setData(Qt::ToolTipRole, monster.description);
        item->setData(Qt::UserRole + 2, monster.abilitys);
        ui->monsterList->addItem(item); //adds monster to list
    }





}

