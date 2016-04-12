#include "calculationmod.h"
#include <iostream>

using namespace std;
void calculationMod::set_dt(float ddt){
    dt = ddt;
}
calculationMod::calculationMod()
{
    
}

void calculationMod::doStep(planet* massOfPlanets, int n){
    moveAllUnits(massOfPlanets, n);
}

void calculationMod::moveAllUnits(planet* massOfPlanets, int n){
    for (int i = 0; i < n; i++){
        moveAllUnitsOnPlanet(massOfPlanets[i]);
    }
}

void calculationMod::moveAllUnitsOnPlanet(planet &onePlanet){
    sector **massOfSectors = onePlanet.getMassOfSectors();
    
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 8; j++){
            bool teamFlag = true;   // true для первого игрока
            list<unit> &listOfUnits1 = massOfSectors[i][j].getListOfUnits1();
            moveUnitsInList(listOfUnits1, massOfSectors, i , j, teamFlag);
            
            teamFlag = false;       // false для второго игрока
            list<unit> &listOfUnits2 = massOfSectors[i][j].getListOfUnits2();
            moveUnitsInList(listOfUnits2, massOfSectors, i , j, teamFlag);
        }
    }
}

void calculationMod::moveUnitsInList(list<unit> &currentListOfUnits, sector **massOfSectors, int i, int j, bool teamFlag){
    list<unit>::iterator oneOfUnits = currentListOfUnits.begin();
    while(oneOfUnits != currentListOfUnits.end())
    {
        if (oneOfUnits->isRupture()){
            oneOfUnits->setKeyRupture(false);
        }
        else
        {
            switch (oneOfUnits->getMoveType()) {
                case standartMove:{
                    double diff_X = massOfSectors[i][j].getDifference_X();
                    double diff_Y = massOfSectors[i][j].getDifference_Y();
                    moveStandartUnit(*oneOfUnits, diff_X, diff_Y, teamFlag);
                    break;
                }
                default:
                    break;
            }
            
            if (oneOfUnits->isSectorChange()){
                addToNextSector(*oneOfUnits, massOfSectors, i, j, teamFlag);
                oneOfUnits = currentListOfUnits.erase(oneOfUnits);
                oneOfUnits--;
            }
        }
        
        oneOfUnits++;
    }
}

void calculationMod::moveStandartUnit(unit &oneUnit, double differecne_X, double differecne_Y, bool teamFlag){
    double partOfWay =  oneUnit.getSpeed() / 1000.0;
    // Конструкция будет изменена, но щас так удобно для отладки!!!
    if (teamFlag){
        oneUnit.changeCoordinate(differecne_X * partOfWay, differecne_Y * partOfWay);
        oneUnit.writeCoordinates();   // Временно для отладки
    }
    else
    {
        oneUnit.changeCoordinate(-differecne_X * partOfWay, -differecne_Y * partOfWay);
        //oneUnit.writeCoordinates();   // Временно для отладки
    }
    oneUnit.incrementCountSectorChange();
    //oneUnit.writeCoordinates();   // Временно для отладки
}

void calculationMod::addToNextSector(unit &oneUnit, sector **massOfSectors, int i, int j,  bool teamFlag){
    oneUnit.clearCountSectorChange();
    int indexOfNextSector = 0;
    indexOfNextSector = getIndexOfNextSector(oneUnit, j, teamFlag);
    
    if (teamFlag){
        list<unit> &nextListOfUnits = massOfSectors[i][indexOfNextSector].getListOfUnits1();
        nextListOfUnits.push_back(oneUnit);
    }
    else
    {
        list<unit> &nextListOfUnits = massOfSectors[i][indexOfNextSector].getListOfUnits2();
        nextListOfUnits.push_back(oneUnit);
    }
}

int calculationMod::getIndexOfNextSector(unit &oneUnit, int indexOfSector, bool teamFlag){
    int indexOfNextSector = 0;
    
    if (teamFlag){
        if (indexOfSector == 7){
            indexOfNextSector = 0;
        }
        else
        {
            indexOfNextSector = indexOfSector + 1;
            oneUnit.setKeyRupture(true);
        }
    }
    else
    {
        if (indexOfSector == 0){
            indexOfNextSector = 7;
            oneUnit.setKeyRupture(true);
        }
        else
        {
            indexOfNextSector = indexOfSector - 1;
        }
    }
    
    return indexOfNextSector;
}
