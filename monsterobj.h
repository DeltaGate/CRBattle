#ifndef MONSTEROBJ_H
#define MONSTEROBJ_H

#include <string>
#include <vector>
#include <QString>
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
    vector<string> abilitys;

private:

};



#endif // MONSTEROBJ_H
