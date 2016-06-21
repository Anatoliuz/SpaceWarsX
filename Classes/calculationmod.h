#ifndef CALCULATIONMOD_H
#define CALCULATIONMOD_H

#include <vector>
#include <planet.h>
#include <rib.h>
#include <shell.h>

//#include <unit.h>

class calculationMod
{
public:
    calculationMod();
    
    int getNumberOfWiner(vector<planet> &vectorOfPlanets, vector<rib> &vectorOfRibs, int numbOfPlayers);

    // Осуществляет все действия необходимые для одного рендера
    void doStep(vector<planet> &vectorOfPlanets, vector<rib> &vectorOfRibs, vector<shell> &vectorOfShells, int numbOfPlayers);
    // Даёт юнитам сигнал на перелёт на другую планету
    void changeUnitsState(planet &currentPlanet, int state, int n, int playerNumber);
    // Создает здание на планете
    void createBuilding(planet &onePlanet, int playerNumber);
    // Возвращает вектор всех юнитов
    vector<unit> getVectorOfUnits(vector<planet> vectorOfPlanets, vector<rib> vectorOfRibs, int numbOfPlayers);

private:
    // Осуществляет движение всех юнитов
    void moveAllUnits(vector<planet> &vectorOfPlanets, vector<rib> &vectorOfRibs, int numbOfPlayers);

    // Осуществляет движение всех юнитов на планете
    void moveAllUnitsOnPlanet(planet &onePlanet, int numbOfPlayers, vector<rib> &vectorOfRibs);
    // Осуществляет движение всех юнитов, хранящихся в listOfUnits сектора
    void moveUnitsInSectorList(list<unit> &listOfUnits, sector **currentMassOfSectors, int i, int j, int playerNumber, vector<rib> &vectorOfRibs, planet &onePlanet);
    // Осуществляет движение юнита в секторе с типом движния standartMove
    void moveStandartUnit(unit &oneUnit, double differecne_X, double differecne_Y, int playerNumber);
    // Осуществляет переход юнита в следующую ячейку
    void addToSectorOrRib(unit &oneUnit, sector **currentMassOfSectors, int i, int j, int playerNumber, vector<rib> &vectorOfRibs, planet &onePlanet);
    // Осуществляет переход юнита в следующий сектор
    void addToSector(unit &oneUnit, sector **massOfSectors, int i, int j, int playerNumber);
    // Осуществляет переход юнита в ребро
    void addToRib(unit &oneUnit, int i, int j, int playerNumber, vector<rib> &vectorOfRibs, planet &onePlanet);
    // Возвращает индек следующего сектора и устанавливает флажок разрыва, если требуется
    int getIndexOfNextSectorAndSetRupture(unit &oneOfUnits, int j, int playerNumber);

    // Осуществляет движение всех юнитов в ребре
    void moveAllUnitsInRib(rib &oneRib, vector<planet> &vectorOfPlanets, int numbOfPlayers);
    // Осуществляет движение всех юнитов, хранящихся в listOfUnits ребра
    void moveUnitsInRibList(list<ribStruct> &listOfUnits ,vector<planet> &vectorOfPlanets, int playerNumber);
    // Осуществляет движение юнита в ребре с типом движния standartRibMove
    void moveStandartUnitInRib(ribStruct &oneRibStruct);
    // Осуществляет переход юнита в сектор
    void addToPlanet(ribStruct &oneOfRibStruct, vector<planet> &vectorOfPlanets,int playerNumber);


    // Осуществляет бой между всеми юнитами
    void fightAllUnits(vector<planet> &vectorOfPlanets, vector<shell> &vectorOfShells, int numbOfPlayers);
    // Осуществляет бой между всеми юнитами на планете
    void fightOnPlanet(planet &onePlanet, vector<shell> &vectorOfShells, int numbOfPlayers);
    // Осуществляет стрельбу для всех юнитов, хранищихся в listOfUnits
    void fight(list<unit> &listOfUnits, planet &onePlanet, int i, int j, vector<shell> &vectorOfShells, int playerNumber, int numbOfPlayers);
    // Осуществляет стрельбу юнита с типом атаки standartAttack
    void AttackStandartUnit(unit &oneUnit, planet &onePlanet, int orbit, int area, vector<shell> &vectorOfShells, int playerNumber, int numbOfPlayers);
    // Возвращает true,  если выстрел был совершён при этом один из вражеских юнитов теряет жизни
    bool shootInFirstUnit(list<unit> &listOfUnits, int damage, coordinate_X_Y &shellFinish);
    // Возвращает true,  если выстрел был совершён при здание теряет жизни
    bool shootInBuilding(building &oneBuilding, int damage, coordinate_X_Y &shellFinish);

    // Удаляет все мертые (разрушенные) объекты
    void deleteALLDeadObjectsOnPlanet(planet &onePlanet, int numbOfPlayers);
    // Удаляет мертвые юниты из listOfUnits
    void deleteDeadUnitsInList(list<unit> &listOfUnits, planet &onePlanet, int playerNumber);


    // Создает юниты на всех планетах
    void createAllUnits(vector<planet> &vectorOfPlanets);
    // Создаёт юниты на планете
    void createOnPlanet(planet &onePlanet);
};

#endif // CALCULATIONMOD_H
