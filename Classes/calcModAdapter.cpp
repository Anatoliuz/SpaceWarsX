#include "calcModAdapter.h"
#include <assert.h>

#include <iostream>

calcModAdapter::~calcModAdapter()
{
    delete calcMod;
    if(PRINTONSCREEN) cout << "~calcModAdapter()\n";
}

vector<unit> calcModAdapter::getVectorOfUnits(vector<planet> vectorOfPlanets, vector<rib> vectorOfRibs, int numbOfPlayers)
{
    return calcMod->getVectorOfUnits(vectorOfPlanets, vectorOfRibs, numbOfPlayers);
}

calcModAdapter::calcModAdapter(int playerNumber)
{
    calcMod = new calculationMod();
    data    = new dataModel(0, playerNumber); // 0 планет и номер игрока

    /*
    // создание планет, можно убрать
    for (size_t i = 0; i < numberOfPlanets; i++) {
        data -> planets.push_back(planet(i, 40 * (i % 3), i * 40, data -> numberOfPlayers)); // prost ppc
    }
    for (int i = 0; i < numberOfPlanets - 1; i++) { // создание ребра каждый с каждым
        for (int j = i + 1; j < numberOfPlanets; j++) {
            data -> ribs.push_back(rib(data -> planets[i], data -> planets[j], data -> numberOfPlayers)); // prost ppc
        }
    }*/

    if(PRINTONSCREEN) cout << "calcModAdapter()\n";
}


void calcModAdapter::createBuilding (int planetId, int playerId)
{
    cout << "\n createBuilding " << planetId << " " << playerId << "\n";
    planet& currentPlanet = findPlanet(planetId);
    calcMod -> createBuilding(currentPlanet, playerId);
}


void calcModAdapter::move (int planetId1, int planetId2, int number, int player)
{
    planet& currentPlanet = findPlanet(planetId1);
    calcMod -> changeUnitsState (currentPlanet, planetId2, number, player);
    cout << "\n " << planetId1 << " " << planetId2 << " " << number << " " << player << "\n ";
}

void calcModAdapter::doStep()
{
    cout << "\ndoStep\n";
    calcMod -> doStep(data -> planets, data -> ribs, data -> shells, data -> numberOfPlayers);
}


planet& calcModAdapter::findPlanet(int planetId)
{
    for ( size_t i = 0; i < data -> planets.size(); i++) {
        if (planetId == data -> planets[i].getNumberOfPlanet()) {
            return data -> planets[i];
        }
    }
    assert (false); // не найдена планета откуда посылаются корабли
}
