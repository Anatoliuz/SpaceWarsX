#include "sector.h"


sector::sector()
{

}

sector::sector(double coord_X, double coord_Y, double diff_X, double diff_Y, int numberOfPlayers)
{
    start.x = coord_X;
    start.y = coord_Y;
    finish.x = coord_X;
    finish.y = coord_Y;
    differecne_X = diff_X;
    differecne_Y = diff_Y;

    connectPlanet_1 = -1;
    connectPlanet_2 = -1;

    massOfPlayersListsOfUnits = new list<unit>[numberOfPlayers];
    
    
    //!!!
    
}

void sector::changeCoordinates(double start_X, double start_Y, double finish_X, double finish_Y){
    start.x += start_X;
    start.y += start_Y;
    finish.x += finish_X;
    finish.y += finish_Y;
}

void sector::createUnit1(int planetNumber){
    unit newUnit(start.x, start.y, planetNumber);
    (massOfPlayersListsOfUnits[0]).push_back(newUnit);
}

void sector::createUnit2(int planetNumber){
    unit newUnit(finish.x, finish.y, planetNumber);
    massOfPlayersListsOfUnits[1].push_back(newUnit);
}

void sector::setConnectPlanet_1(int planetNumber){
    connectPlanet_1 = planetNumber;
}

void sector::setConnectPlanet_2(int planetNumber){
    connectPlanet_2 = planetNumber;
}

coordinate_X_Y sector::getStart(){
    return start;
}

coordinate_X_Y sector::getFinish(){
    return finish;
}

double sector::getDifference_X(){
    return differecne_X;
}

double sector::getDifference_Y(){
    return differecne_Y;
}

int sector::getConnectPlanet_1(){
    return connectPlanet_1;
}

int sector::getConnectPlanet_2(){
    return connectPlanet_2;
}

list<unit>* sector::getMassOfPlayersLists(){
    return massOfPlayersListsOfUnits;
}
