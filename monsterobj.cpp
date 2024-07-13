#include "monsterobj.h"

MonsterObj::MonsterObj() {
}

MonsterObj MonsterObj::createMonsters(int response){
    switch (response) {

    case 0: {
        MonsterObj goblin;
        goblin.name = "Goblin";
        goblin.type = "Goblinoid";
        goblin.cr = 0.125;
        goblin.abilitys = {"Short Sword, 1d8+1", "Short Bow, 1d6+1", "Stink Bomb, 1d4+3"};
        goblin.description = "A greesy little shit";
        return goblin;
    }

    case 1: {
        MonsterObj josh;
        josh.name = "Joshy";
        josh.type = "Demon King";
        josh.cr = 12;
        josh.abilitys = {"Head shots only, wins the game"};
        josh.description = "You don't even want to know.";
        return josh;
    }

    default:
        break;
    }
}
