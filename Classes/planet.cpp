#include "planet.h"
#include <math.h>
#include "cocos2d.h"

using namespace std;

coordinate_X_Y planet::get_planet_coordinates()
{
    return coordinate;
}
double planet::get_planet_radius(){
    return radiusOfPlanet;
}
planet::planet()
{
    radiusOfPlanet = 100;
    radiusOfOrbit = 20;
    coordinate.x = 200;
    coordinate.y = 200;
}

planet::planet(int planetNumber, double coord_X, double coord_Y, int numberOfPlayers)
{
    
    numberOfPlanet = planetNumber;
    this->numberOfPlayers = numberOfPlayers;
    owner = -1;

    coordinate.x = coord_X;
    coordinate.y = coord_Y;
    radiusOfPlanet = 100;
    radiusOfOrbit = 20;

    massOfUnitsCount = new int[numberOfPlayers];

    double straightLine = radiusOfPlanet - radiusOfOrbit / 2;
    double diagonal = straightLine / sqrt(2);
    double diagonalDifference = radiusOfOrbit / sqrt(2);

    int numbOfOrbits = 5;
    int numbOfAreas = 8;
    massOfSectors = new sector*[numbOfOrbits];
    for (int i = 0; i < numbOfOrbits; i++){
         massOfSectors[i] = new sector[numbOfAreas];
    }

    for (int i = 0; i < numbOfOrbits; i++){
        straightLine += radiusOfOrbit;
        diagonal += diagonalDifference;

        double bigDifference = diagonal;
        double smallDifference = straightLine - diagonal;

        massOfSectors[i][0] = sector(coordinate.x, coordinate.y, bigDifference, -smallDifference, numberOfPlayers);
        massOfSectors[i][1] = sector(coordinate.x, coordinate.y, smallDifference, -bigDifference, numberOfPlayers);
        massOfSectors[i][2] = sector(coordinate.x, coordinate.y, -smallDifference, -bigDifference, numberOfPlayers);
        massOfSectors[i][3] = sector(coordinate.x, coordinate.y, -bigDifference, -smallDifference, numberOfPlayers);
        massOfSectors[i][4] = sector(coordinate.x, coordinate.y, -bigDifference, smallDifference, numberOfPlayers);
        massOfSectors[i][5] = sector(coordinate.x, coordinate.y, -smallDifference, bigDifference, numberOfPlayers);
        massOfSectors[i][6] = sector(coordinate.x, coordinate.y, smallDifference, bigDifference, numberOfPlayers);
        massOfSectors[i][7] = sector(coordinate.x, coordinate.y, bigDifference, smallDifference,numberOfPlayers);

        massOfSectors[i][0].changeCoordinates(0, straightLine, diagonal, diagonal);
        massOfSectors[i][1].changeCoordinates(diagonal, diagonal, straightLine, 0);
        massOfSectors[i][2].changeCoordinates(straightLine, 0, diagonal, -diagonal);
        massOfSectors[i][3].changeCoordinates(diagonal, -diagonal, 0, -straightLine);
        massOfSectors[i][4].changeCoordinates(0, -straightLine, -diagonal, -diagonal);
        massOfSectors[i][5].changeCoordinates(-diagonal, -diagonal, -straightLine, 0);
        massOfSectors[i][6].changeCoordinates(-straightLine, 0, -diagonal, diagonal);
        massOfSectors[i][7].changeCoordinates(-diagonal, diagonal, 0, straightLine);
    }



    // Отладочные данные моделирующие тестовую карту
    if (planetNumber == 0){
        massOfUnitsCount[0] = 5;
        massOfUnitsCount[1] = 1;
        massOfSectors[0][0].createUnit1(planetNumber);
        massOfSectors[0][5].createUnit1(planetNumber);
        massOfSectors[0][3].createUnit2(planetNumber);
//        massOfSectors[1][3].createUnit2(planetNumber);
        massOfSectors[2][7].createUnit1(planetNumber);
//        massOfSectors[2][1].createUnit2(planetNumber);
        massOfSectors[1][4].createUnit1(planetNumber);
        massOfSectors[1][2].createUnit1(planetNumber);
//        massOfSectors[1][6].createUnit2(planetNumber);
    }
    else if (planetNumber == 1){
        massOfUnitsCount[1] = 1;
        massOfSectors[0][6].createUnit2(planetNumber);
    }
    else if (planetNumber == 2){
        massOfUnitsCount[0] = 1;
        massOfSectors[0][1].createUnit1(planetNumber);
    }

}

bool planet::isWar(){
    int numberOfUnits1 = 0;
    int numberOfUnits2 = 0;

    for (int i = 0; i < numberOfPlayers; i++){
        if (i % 2 == 0)
            numberOfUnits1 += massOfUnitsCount[i];
        else
            numberOfUnits2 += massOfUnitsCount[i];
    }

    if (vectorOfBuildings.size() > 0){
        if (owner % 2 == 0)
            numberOfUnits1 += vectorOfBuildings.size();
        else
            numberOfUnits2 += vectorOfBuildings.size();
    }

    if (numberOfUnits1 > 0 && numberOfUnits2 > 0)
        return true;
    else
        return false;
}

void planet::incrementUnitsCount(int playerNumber){
    massOfUnitsCount[playerNumber]++;
}

void planet::decrementUnitsCount(int playerNumber){
    massOfUnitsCount[playerNumber]--;
}

void planet::setOwner(int playerNumber){
    owner = playerNumber;
}

int planet::getNumberOfPlanet(){
    return numberOfPlanet;
}

int planet::getOwner(){
    return owner;
}

coordinate_X_Y planet::getCoordinates(){
    return coordinate;
}

double planet::getRadiusOfPlanet(){
    return radiusOfPlanet;
}

int planet::getUnitsCount(int playerNumber){
    return massOfUnitsCount[playerNumber];
}

sector** planet::getMassOfSectors(){
    return massOfSectors;
}

vector<building>& planet::getVectorOfBuildings(){
    return vectorOfBuildings;
}
