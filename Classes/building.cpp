#include "building.h"

building::building()
{

}

building::building(coordinate_X_Y coordinate, int leftArea, int rightArea, int numberOfBuilding){
    this->coordinate = coordinate;
    this->leftArea = leftArea;
    this->rightArea = rightArea;
    this->numberOfBuilding = numberOfBuilding;

    health = 150;
    orbitForCreation = 0;
    create = 44;
    countCreate = 0;
}

bool building::isReadyToCreate(){
    return create == countCreate;
}

bool building::isDead(){
    return health <= 0;
}

void building::changeOrbitForCreation(){
    orbitForCreation++;

    if (orbitForCreation == 5)
        orbitForCreation = 0;
}

void building::incrementCountCreate(){
    countCreate++;
}

void building::clearCountCreate(){
    countCreate = 0;
}

void building::takeDamage(int damage){
    health -= damage;
}

int building::getHealth(){
    return health;
}

int building::getNumberOfBuilding(){
    return numberOfBuilding;
}

coordinate_X_Y building::getCoordinate(){
    return coordinate;
}

int building::getOrbitForCreation(){
    return orbitForCreation;
}

int building::getLeftArea(){
    return leftArea;
}

int building::getRightArea(){
    return rightArea;
}
