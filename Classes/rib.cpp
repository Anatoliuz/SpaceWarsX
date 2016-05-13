#include "rib.h"

#include <iostream>
using namespace std;

rib::rib()
{

}

rib::rib(planet &firstPlanet, planet &secondPlanet, int numberOfPlayers){
    numberOne = firstPlanet.getNumberOfPlanet();
    numberTwo = secondPlanet.getNumberOfPlanet();
    massOfPlayersListsOfStructs = new list<ribStruct>[numberOfPlayers];

    double diff_X = secondPlanet.getCoordinates().x - firstPlanet.getCoordinates().x;
    double diff_Y = secondPlanet.getCoordinates().y - firstPlanet.getCoordinates().y;
    int firstClosestSector = determineClosestSector(diff_X, diff_Y);

    int leftConnect = 0;
    int rightConnect = 0;
    determineSectorsOfConnection(firstClosestSector, leftConnect, rightConnect);

    //cout << leftConnect << rightConnect <<"\n\n";      //Для отладки

    sector **massOfSectors_1 = firstPlanet.getMassOfSectors();
    sector **massOfSectors_2 = secondPlanet.getMassOfSectors();
    for (int i = 0; i < 5; i++){
        massOfSectors_1[i][leftConnect].setConnectPlanet_1(numberTwo);
        massOfSectors_1[i][rightConnect].setConnectPlanet_2(numberTwo);
        massOfSectors_2[i][leftConnect].setConnectPlanet_2(numberOne);
        massOfSectors_2[i][rightConnect].setConnectPlanet_1(numberOne);
    }

    //cout << firstClosestSector << "\n\n";   //Для отладки
}

int rib::getNumb1(){
    return numberOne;
}

int rib::getNumb2(){
    return numberTwo;
}

list<ribStruct>* rib::getMassOfPlayersLists(){
    return massOfPlayersListsOfStructs;
}

int rib::determineClosestSector(double diff_X, double diff_Y){
    int closestSector = 0;

    if (diff_X >= 0)
        if (diff_Y > 0)
            if (diff_Y > diff_X)
                closestSector = 0;
            else
                closestSector = 1;
        else
            if (diff_X > -diff_Y)
                closestSector = 2;
            else
                closestSector = 3;
    else
        if (diff_Y < 0)
            if (-diff_Y > -diff_X)
                closestSector = 4;
            else
                closestSector = 5;
        else
            if (-diff_X > diff_Y)
                closestSector = 6;
            else
                closestSector = 7;

    return closestSector;
}

void rib::determineSectorsOfConnection(int closestSector, int &leftConnect, int &rightConnect){
    switch (closestSector) {
    case 0:
        leftConnect = 6;
        rightConnect = 2;
        break;
    case 1:
        leftConnect = 7;
        rightConnect = 3;
        break;
    case 2:
        leftConnect = 0;
        rightConnect = 4;
        break;
    case 3:
        leftConnect = 1;
        rightConnect = 5;
        break;
    case 4:
        leftConnect = 2;
        rightConnect = 6;
        break;
    case 5:
        leftConnect = 3;
        rightConnect = 7;
        break;
    case 6:
        leftConnect = 4;
        rightConnect = 0;
        break;
    case 7:
        leftConnect = 5;
        rightConnect = 1;
        break;
    default:
        break;
    }
}
