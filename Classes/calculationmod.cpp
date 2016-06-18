#include "calculationmod.h"
#include <iostream>
#include <math.h>

using namespace std;


calculationMod::calculationMod()
{

}

void calculationMod::doStep(vector<planet> &vectorOfPlanets, vector<rib> &vectorOfRibs,
                            vector<shell> &vectorOfShells, int numbOfPlayers){

    moveAllUnits(vectorOfPlanets, vectorOfRibs, numbOfPlayers);
    fightAllUnits(vectorOfPlanets, vectorOfShells, numbOfPlayers);
    createAllUnits(vectorOfPlanets);
}

void calculationMod::changeUnitsState(planet &currentPlanet, int state, int n, int playerNumber){
    sector **massOfSectors = currentPlanet.getMassOfSectors();

    for (int j = 0; j < 8; j++){
        for (int i = 0; i < 5; i++){
            list<unit> *massOfPlayersList = massOfSectors[i][j].getMassOfPlayersLists();
            list<unit> &listOfUnits = massOfPlayersList[playerNumber];

            list<unit>::iterator oneOfUnits = listOfUnits.begin();
            while(oneOfUnits != listOfUnits.end())
            {
                if (n != 0){
                    n--;
                    oneOfUnits->setTransportationStatus(state);
                    oneOfUnits++;
                }
                else
                    break;
            }
        }
    }
}

void calculationMod::createBuilding(planet &onePlanet, int playerNumber){
    vector<building> &vectorOfBuildings = onePlanet.getVectorOfBuildings();

    if (vectorOfBuildings.size() == 1 && !onePlanet.isWar() && onePlanet.getOwner() == playerNumber){
        int numberOfBuilding = vectorOfBuildings[0].getNumberOfBuilding();
        coordinate_X_Y coordinate = onePlanet.getCoordinates();

        if (numberOfBuilding == 1){
            coordinate.y -= onePlanet.getRadiusOfPlanet();
            building newBuilding(coordinate, 3, 4, 2);
            vectorOfBuildings.push_back(newBuilding);
        }
        else
        {
            coordinate.y += onePlanet.getRadiusOfPlanet();
            building newBuilding(coordinate, 7, 0, 1);
            vectorOfBuildings.push_back(newBuilding);
        }
    }
    else if (vectorOfBuildings.size() == 0 && !onePlanet.isWar() && onePlanet.getUnitsCount(playerNumber) > 0)
    {
        onePlanet.setOwner(playerNumber);
        coordinate_X_Y coordinate = onePlanet.getCoordinates();
        coordinate.y += onePlanet.getRadiusOfPlanet();
        building newBuilding(coordinate, 7, 0, 1);
        vectorOfBuildings.push_back(newBuilding);
    }

    cout << "Создали здание!\n";   // Для отладки
}

vector<unit> calculationMod::getVectorOfUnits(vector<planet> vectorOfPlanets, vector<rib> vectorOfRibs, int numbOfPlayers){
    vector<unit> vectorOfUnits;

    for (unsigned int i = 0; i < vectorOfPlanets.size(); i++){
        sector **massOfSectors = vectorOfPlanets[i].getMassOfSectors();

        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 8; j++){
                list<unit> *massOfPlayersList = massOfSectors[i][j].getMassOfPlayersLists();

                for (int playerNumber = 0; playerNumber < numbOfPlayers; playerNumber++){
                    list<unit> listOfUnits = massOfPlayersList[playerNumber];

                    list<unit>::iterator oneOfUnits = listOfUnits.begin();
                    while(oneOfUnits != listOfUnits.end())
                    {
                        vectorOfUnits.push_back(*oneOfUnits);
                        oneOfUnits++;
                    }
                }
            }
        }
    }

    for (unsigned int i = 0; i < vectorOfRibs.size(); i++){
        list<ribStruct>* massOfPlayersList = vectorOfRibs[i].getMassOfPlayersLists();

        for (int playerNumber = 0; playerNumber < numbOfPlayers; playerNumber++){
            list<ribStruct> listOfUnits = massOfPlayersList[playerNumber];

            list<ribStruct>::iterator oneOfRibStructs = listOfUnits.begin();
            while(oneOfRibStructs != listOfUnits.end())
            {
                vectorOfUnits.push_back(oneOfRibStructs->oneUnit);
                oneOfRibStructs++;
            }
        }
    }

    return vectorOfUnits;
}


// Далее идут приватные функции

void calculationMod::moveAllUnits(vector<planet> &vectorOfPlanets, vector<rib> &vectorOfRibs, int numbOfPlayers){
    for (unsigned int i = 0; i < vectorOfPlanets.size(); i++){
        moveAllUnitsOnPlanet(vectorOfPlanets[i], numbOfPlayers, vectorOfRibs);
    }

    for (unsigned int i = 0; i < vectorOfRibs.size(); i++){
        moveAllUnitsInRib(vectorOfRibs[i], vectorOfPlanets, numbOfPlayers);
    }
}

void calculationMod::moveAllUnitsOnPlanet(planet &onePlanet, int numbOfPlayers, vector<rib> &vectorOfRibs){
    sector **massOfSectors = onePlanet.getMassOfSectors();

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 8; j++){
            list<unit> *massOfPlayersList = massOfSectors[i][j].getMassOfPlayersLists();

            for (int playerNumber = 0; playerNumber < numbOfPlayers; playerNumber++){
                list<unit> &listOfUnits = massOfPlayersList[playerNumber];
                moveUnitsInSectorList(listOfUnits, massOfSectors, i , j, playerNumber, vectorOfRibs, onePlanet);
            }
        }
    }
}

void calculationMod::moveUnitsInSectorList(list<unit> &currentListOfUnits, sector **massOfSectors, int i,
                                           int j, int playerNumber, vector<rib> &vectorOfRibs, planet &onePlanet){

    list<unit>::iterator oneOfUnits = currentListOfUnits.begin();
    while(oneOfUnits != currentListOfUnits.end())
    {
        if (oneOfUnits->isRupture()){
            oneOfUnits->setKeyRupture(false);
            oneOfUnits++;
        }
        else
        {
            switch (oneOfUnits->getMoveType()) {
            case standartMove:{
                double diff_X = massOfSectors[i][j].getDifference_X();
                double diff_Y = massOfSectors[i][j].getDifference_Y();
                moveStandartUnit(*oneOfUnits, diff_X, diff_Y, playerNumber);
                break;
            }
            default:
                break;
            }

            if (!oneOfUnits->isRecharge())
                oneOfUnits->incrementCountRecharge();

            if (oneOfUnits->isChange()){
                addToSectorOrRib(*oneOfUnits, massOfSectors, i, j, playerNumber, vectorOfRibs, onePlanet);
                currentListOfUnits.erase(oneOfUnits++);
                //oneOfUnits--;
            }
            else
                oneOfUnits++;
        }

        //oneOfUnits++;
    }
}

void calculationMod::moveStandartUnit(unit &oneUnit, double differecne_X, double differecne_Y, int playerNumber){
    double partOfWay = 1.0 / oneUnit.getChange();

    // Позже объединить с функцией moveStandartUnitInRib
    // Конструкция будет изменена, но щас так удобно для отладки!!! (+ корректировка moveUnitsInSectorList)
    if (playerNumber % 2 == 0){
        oneUnit.changeCoordinate(differecne_X * partOfWay, differecne_Y * partOfWay);
        cout << "Первый корабль " << oneUnit.getHealth() << " " << oneUnit.getCurrentPlanet() << " ";
        oneUnit.writeCoordinates();   // Временно для отладки
    }
    else
    {
        oneUnit.changeCoordinate(-differecne_X * partOfWay, -differecne_Y * partOfWay);
        cout << "Второй корабль " << oneUnit.getHealth() << " " << oneUnit.getCurrentPlanet() << " ";
        oneUnit.writeCoordinates();   // Временно для отладки
    }

    oneUnit.incrementCountChange();
    //oneUnit.writeCoordinates();   // Временно для отладки
}

void calculationMod::addToSectorOrRib(unit &oneUnit, sector **massOfSectors, int i, int j,
                                      int playerNumber, vector<rib> &vectorOfRibs, planet &onePlanet){

    oneUnit.clearCountChange();
    int transportationStatus = oneUnit.getTransportationStatus();
    int connectPlanet = 0;

    if (playerNumber % 2 == 0)
        connectPlanet = massOfSectors[i][j].getConnectPlanet_1();
    else
        connectPlanet = massOfSectors[i][j].getConnectPlanet_2();

    if (transportationStatus == -1 || transportationStatus != connectPlanet)
        addToSector(oneUnit, massOfSectors, i, j, playerNumber);
    else
        addToRib(oneUnit, i, j, playerNumber, vectorOfRibs, onePlanet);
}

void calculationMod::addToSector(unit &oneUnit, sector **massOfSectors, int i, int j, int playerNumber){
    oneUnit.setChange(round(900 / oneUnit.getSpeed()));
    int indexOfNextSector = 0;
    indexOfNextSector = getIndexOfNextSectorAndSetRupture(oneUnit, j, playerNumber);
    list<unit> *massOfPlayersList = massOfSectors[i][indexOfNextSector].getMassOfPlayersLists();
    list<unit> &nextListOfUnits = massOfPlayersList[playerNumber];
    nextListOfUnits.push_back(oneUnit);
}

void calculationMod::addToRib(unit &oneUnit, int i, int j, int playerNumber, vector<rib> &vectorOfRibs, planet &onePlanet){
    int min = 0;
    int max = 0;

    if (oneUnit.getTransportationStatus() < oneUnit.getCurrentPlanet()){
        min = oneUnit.getTransportationStatus();
        max = oneUnit.getCurrentPlanet();
    }
    else
    {
        min = oneUnit.getCurrentPlanet();
        max = oneUnit.getTransportationStatus();
    }

    for (unsigned int k = 0; k < vectorOfRibs.size(); k++){
        if (vectorOfRibs[k].getNumb1() == min && vectorOfRibs[k].getNumb2() == max){
            oneUnit.setKeyRupture(true);

            ribStruct newStruct;
            newStruct.oneUnit = oneUnit;
            newStruct.orbit = i;
            newStruct.area = j;
            newStruct.diff_X = 0;
            newStruct.diff_Y = 0;

            list<ribStruct> *massOfPlayersList = vectorOfRibs[k].getMassOfPlayersLists();
            list<ribStruct> &nextListOfStructs = massOfPlayersList[playerNumber];
            nextListOfStructs.push_back(newStruct);
            onePlanet.decrementUnitsCount(playerNumber);
            break;
        }
    }

    cout << "Перелёт в ребро!!!\n";   // Для отладки
}

int calculationMod::getIndexOfNextSectorAndSetRupture(unit &oneUnit, int indexOfSector, int playerNumber){
    int indexOfNextSector = 0;

    if (playerNumber % 2 == 0){
        if (indexOfSector == 7)
            indexOfNextSector = 0;
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
            indexOfNextSector = indexOfSector - 1;
    }

    return indexOfNextSector;
}



void calculationMod::moveAllUnitsInRib(rib &oneRib, vector<planet> &vectorOfPlanets, int numbOfPlayers){
    list<ribStruct>* massOfPlayersList = oneRib.getMassOfPlayersLists();

    for (int playerNumber = 0; playerNumber < numbOfPlayers; playerNumber++){
        list<ribStruct> &listOfUnits = massOfPlayersList[playerNumber];
        moveUnitsInRibList(listOfUnits, vectorOfPlanets, playerNumber);
    }
}

void calculationMod::moveUnitsInRibList(list<ribStruct> &listOfUnits, vector<planet> &vectorOfPlanets, int playerNumber){
    list<ribStruct>::iterator oneOfRibStruct = listOfUnits.begin();

    while(oneOfRibStruct != listOfUnits.end())
    {
        if (oneOfRibStruct->oneUnit.isRupture()){
            oneOfRibStruct->oneUnit.setKeyRupture(false);

            // Потом загнать под отдельную функцию
            sector **massOfSectors = vectorOfPlanets[oneOfRibStruct->oneUnit.getTransportationStatus()].getMassOfSectors();
            coordinate_X_Y finish;

            if (playerNumber % 2 == 0)
                finish = massOfSectors[oneOfRibStruct->orbit][oneOfRibStruct->area].getStart();
            else
                finish = massOfSectors[oneOfRibStruct->orbit][oneOfRibStruct->area].getFinish();

            coordinate_X_Y start = oneOfRibStruct->oneUnit.getCoordinate();
            oneOfRibStruct->diff_X = finish.x - start.x;
            oneOfRibStruct->diff_Y = finish.y - start.y;
            double ribDistance = sqrt(pow(oneOfRibStruct->diff_X, 2) + pow(oneOfRibStruct->diff_Y, 2));
            double sectorDistance = 200;    // Предварительный вариант константы
            int change = round(900 / oneOfRibStruct->oneUnit.getSpeed() * ribDistance / sectorDistance);
            oneOfRibStruct->oneUnit.setChange(change);
            oneOfRibStruct++;
        }
        else
        {
            switch (oneOfRibStruct->oneUnit.getRibMoveType()) {
            case standartRibMove:{
                moveStandartUnitInRib(*oneOfRibStruct);
                break;
            }
            default:
                break;
            }

            if (!oneOfRibStruct->oneUnit.isRecharge())
                oneOfRibStruct->oneUnit.incrementCountRecharge();

            if (oneOfRibStruct->oneUnit.isChange()){
                addToPlanet(*oneOfRibStruct, vectorOfPlanets, playerNumber);
                listOfUnits.erase(oneOfRibStruct++);
                //oneOfRibStruct--;
            }
            else
                oneOfRibStruct++;
        }

        //oneOfRibStruct++;
    }
}

void calculationMod::moveStandartUnitInRib(ribStruct &oneRibStruct){
    double partOfWay = 1.0 / oneRibStruct.oneUnit.getChange();
    oneRibStruct.oneUnit.changeCoordinate(oneRibStruct.diff_X * partOfWay, oneRibStruct.diff_Y * partOfWay);
    oneRibStruct.oneUnit.writeCoordinates();   // Временно для отладки
    oneRibStruct.oneUnit.incrementCountChange();
}

void calculationMod::addToPlanet(ribStruct &oneOfRibStruct, vector<planet> &vectorOfPlanets, int playerNumber){
    oneOfRibStruct.oneUnit.clearCountChange();

    sector **massOfSectors = vectorOfPlanets[oneOfRibStruct.oneUnit.getTransportationStatus()].getMassOfSectors();
    list<unit> *massOfPlayersList = massOfSectors[oneOfRibStruct.orbit][oneOfRibStruct.area].getMassOfPlayersLists();
    list<unit> &nextListOfUnits = massOfPlayersList[playerNumber];

    oneOfRibStruct.oneUnit.setCurrentPlanet(oneOfRibStruct.oneUnit.getTransportationStatus());
    oneOfRibStruct.oneUnit.setTransportationStatus(-1);
    oneOfRibStruct.oneUnit.setChange(round(900 / oneOfRibStruct.oneUnit.getSpeed()));

    nextListOfUnits.push_back(oneOfRibStruct.oneUnit);
    vectorOfPlanets[oneOfRibStruct.oneUnit.getCurrentPlanet()].incrementUnitsCount(playerNumber);
}



void calculationMod::fightAllUnits(vector<planet> &vectorOfPlanets, vector<shell> &vectorOfShells, int numbOfPlayers){
    vectorOfShells.clear();

    for (unsigned int i = 0; i < vectorOfPlanets.size(); i++){
        if (vectorOfPlanets[i].isWar()){
            fightOnPlanet(vectorOfPlanets[i], vectorOfShells, numbOfPlayers);
            deleteALLDeadObjectsOnPlanet(vectorOfPlanets[i], numbOfPlayers);
        }
    }
}

void calculationMod::fightOnPlanet(planet &onePlanet, vector<shell> &vectorOfShells, int numbOfPlayers){
    sector **massOfSectors = onePlanet.getMassOfSectors();

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 8; j++){
            list<unit> *massOfPlayersList = massOfSectors[i][j].getMassOfPlayersLists();

            for (int playerNumber = 0; playerNumber < numbOfPlayers; playerNumber++){
                list<unit> &listOfUnits = massOfPlayersList[playerNumber];
                fight(listOfUnits, onePlanet, i , j, vectorOfShells, playerNumber, numbOfPlayers);
            }
        }
    }
}

void calculationMod::fight(list<unit> &listOfUnits, planet &onePlanet, int i, int j,
                           vector<shell> &vectorOfShells, int playerNumber, int numbOfPlayers){

    list<unit>::iterator oneOfUnits = listOfUnits.begin();
    while(oneOfUnits != listOfUnits.end())
    {
        if (!oneOfUnits->isRecharge()){
            oneOfUnits->incrementCountRecharge();
        }
        else{
            switch (oneOfUnits->getAttackType()) {
            case standartAttack:{
                AttackStandartUnit(*oneOfUnits, onePlanet, i, j, vectorOfShells, playerNumber, numbOfPlayers);
                break;
            }
            default:
                break;
            }
        }

        oneOfUnits++;
    }
}

void calculationMod::AttackStandartUnit(unit &oneUnit, planet &onePlanet, int orbit,
                                        int area, vector<shell> &vectorOfShells, int playerNumber, int numbOfPlayers){

    sector **massOfSectors = onePlanet.getMassOfSectors();
    bool isShootDone = false;
    int damage = oneUnit.getDamage();
    int nextArea = 0;
    coordinate_X_Y shellFinish;

    if (playerNumber % 2 == 0){    // Вынести if в отдельную функцию
        playerNumber = 1;
        nextArea = area + 1;

        if (nextArea == 8)
            nextArea = 0;
    }
    else
    {
        playerNumber = 0;
        nextArea = area - 1;

        if (nextArea == -1)
            nextArea = 7;
    }

    for (int i = orbit + 1; i >= orbit - 1 && !isShootDone && i >= 0 && i <= 4; i--){
        list<unit> *massOfPlayersList = massOfSectors[i][nextArea].getMassOfPlayersLists();

        for (int playerNumb = playerNumber; playerNumb < numbOfPlayers && !isShootDone; playerNumb += 2){
            list<unit> &listOfUnits = massOfPlayersList[playerNumb];
            isShootDone = shootInFirstUnit(listOfUnits, damage, shellFinish);
        }
    }

    if (!isShootDone){
        list<unit> *massOfPlayersList = massOfSectors[orbit][area].getMassOfPlayersLists();
        list<unit> &listOfUnits = massOfPlayersList[playerNumber];
        isShootDone = shootInFirstUnit(listOfUnits, damage, shellFinish);
    }

    if (!isShootDone && (onePlanet.getOwner() >= 0) && (onePlanet.getOwner() % 2 == playerNumber % 2)){
        vector<building> &vectorOfBuildings = onePlanet.getVectorOfBuildings();

        for (unsigned int i = 0; i < vectorOfBuildings.size() && !isShootDone; i++){
            int leftArea = vectorOfBuildings[i].getLeftArea();
            int rightArea = vectorOfBuildings[i].getRightArea();

            if (orbit == 0 && (area == leftArea || area == rightArea || nextArea == leftArea || nextArea == rightArea))
                isShootDone = shootInBuilding(vectorOfBuildings[i], damage, shellFinish);
            else if (orbit == 1 && (nextArea == leftArea || nextArea == rightArea))
                isShootDone = shootInBuilding(vectorOfBuildings[i], damage, shellFinish);
        }
    }

    if (isShootDone){
        oneUnit.clearCountRecharge();
        coordinate_X_Y shellStart = oneUnit.getCoordinate();
        shell newShell(shellStart, shellFinish);
        vectorOfShells.push_back(newShell);
    }
}

bool calculationMod::shootInFirstUnit(list<unit> &listOfUnits, int damage, coordinate_X_Y &shellFinish){
    list<unit>::iterator oneOfUnits = listOfUnits.begin();
    while(oneOfUnits != listOfUnits.end())
    {
        if (oneOfUnits->isDead())
            oneOfUnits++;
        else
        {
            oneOfUnits->takeDamage(damage);
            shellFinish = oneOfUnits->getCoordinate();
            return true;
        }
    }

    return false;
}

bool calculationMod::shootInBuilding(building &oneBuilding, int damage, coordinate_X_Y &shellFinish){
    if (!oneBuilding.isDead()){
        oneBuilding.takeDamage(damage);
        shellFinish = oneBuilding.getCoordinate();
        return true;
    }
    else
        return false;
}



void calculationMod::deleteALLDeadObjectsOnPlanet(planet &onePlanet, int numbOfPlayers){
    sector **massOfSectors = onePlanet.getMassOfSectors();

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 8; j++){
            list<unit> *massOfPlayersList = massOfSectors[i][j].getMassOfPlayersLists();

            for (int playerNumber = 0; playerNumber < numbOfPlayers; playerNumber++){
                list<unit> &listOfUnits = massOfPlayersList[playerNumber];
                deleteDeadUnitsInList(listOfUnits, onePlanet, playerNumber);
            }
        }
    }

    vector<building> &vectorOfBuildings = onePlanet.getVectorOfBuildings();

    vector<building>::iterator oneOfBuildings = vectorOfBuildings.begin();
    while (oneOfBuildings != vectorOfBuildings.end())
    {
        if (oneOfBuildings->isDead()){
            oneOfBuildings = vectorOfBuildings.erase(oneOfBuildings);
            //oneOfBuildings--;
        }
        else
            oneOfBuildings++;
    }
}

void calculationMod::deleteDeadUnitsInList(list<unit> &listOfUnits, planet &onePlanet, int playerNumber){
    list<unit>::iterator oneOfUnits = listOfUnits.begin();
    while (oneOfUnits != listOfUnits.end())
    {
        if (oneOfUnits->isDead()){
            onePlanet.decrementUnitsCount(playerNumber);
            listOfUnits.erase(oneOfUnits++);
            //oneOfUnits--;
        }
        else
            oneOfUnits++;

        //oneOfUnits++;
    }
}



void calculationMod::createAllUnits(vector<planet> &vectorOfPlanets){
    for (unsigned int i = 0; i < vectorOfPlanets.size(); i++){
        createOnPlanet(vectorOfPlanets[i]);
    }
}

void calculationMod::createOnPlanet(planet &onePlanet){
    sector **massOfSectors = onePlanet.getMassOfSectors();
    vector<building> &vectorOfBuildings = onePlanet.getVectorOfBuildings();

    for (unsigned int i = 0; i < vectorOfBuildings.size(); i++){
        if (vectorOfBuildings[i].isReadyToCreate()){
            vectorOfBuildings[i].clearCountCreate();

            list<unit> *massOfPlayersList;
            int orbitForCreation = vectorOfBuildings[i].getOrbitForCreation();
            coordinate_X_Y coordinate;

            if (onePlanet.getOwner() % 2 == 0){
                int area = vectorOfBuildings[i].getRightArea();
                massOfPlayersList = massOfSectors[orbitForCreation][area].getMassOfPlayersLists();
                coordinate = massOfSectors[orbitForCreation][area].getStart();

            }
            else
            {
                int area = vectorOfBuildings[i].getLeftArea();
                massOfPlayersList = massOfSectors[orbitForCreation][area].getMassOfPlayersLists();
                coordinate = massOfSectors[orbitForCreation][area].getFinish();
            }

            list<unit> &listOfUnits = massOfPlayersList[onePlanet.getOwner()];
            unit newUnit(coordinate.x, coordinate.y, onePlanet.getNumberOfPlanet(), onePlanet.getOwner());

            listOfUnits.push_back(newUnit);
            onePlanet.incrementUnitsCount(onePlanet.getOwner());
            cout << "Unit создан!" << "Жизни - " << vectorOfBuildings[i].getHealth() << "\n";   // Для отладки
        }
        else
        {
            vectorOfBuildings[i].incrementCountCreate();
            cout << "Игнор" << "Жизни - " << vectorOfBuildings[i].getHealth() << "\n";          // Для отладки
        }
    }
}
