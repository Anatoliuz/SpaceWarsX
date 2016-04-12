#ifndef CALCULATIONMOD_H
#define CALCULATIONMOD_H

#include <vector>
#include "planet.h"
#include "unit.h"

class calculationMod
{
private:
    float dt;
public:
    calculationMod();
    void set_dt(float);
    void doStep(planet* massOfPlanets, int n);   // Производ все вычисления необходимые для одного рендера (Будет дорабатываться)

    // Осуществляет движение всех юнитов на всех планетах (Пока без рёбер)
    void moveAllUnits(planet* massOfPlanets, int n);
    // Осуществляет движение всех юнитов на планете
    void moveAllUnitsOnPlanet(planet &onePlanet);
    // Осуществляет движение всех юнитов хранящихся в currentListOfUnits сектора
    void moveUnitsInList(list<unit> &currentListOfUnits, sector **currentMassOfSectors, int i, int j, bool teamFlag);
    // Осуществляет движение юнита в секторе с типом движния standartMove
    void moveStandartUnit(unit &oneUnit, double differecne_X, double differecne_Y, bool teamFlag);
    // Осуществляет переход юнита в следующий сектор
    void addToNextSector(unit &oneOfUnits, sector **currentMassOfSectors, int i, int j, bool teamFlag);
    // Возвращает индек следующего сектора
    int getIndexOfNextSector(unit &oneOfUnits, int j, bool teamFlag);

};

#endif // CALCULATIONMOD_H
