#ifndef MONSTEROBJ_H
#define MONSTEROBJ_H

#include <string>
#include <vector>
#include <QString>
#include <QVector>

using namespace std;

class MonsterObj
{
public:
    MonsterObj();
    MonsterObj createMonsters(int response);
    QString name;
    QString type;
    double cr;
    QString description;
    QVector<QString> abilitys;

private:

};



#endif // MONSTEROBJ_H
