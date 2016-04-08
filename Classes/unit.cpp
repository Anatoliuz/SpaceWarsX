#include "unit.h"
#include <iostream>

using namespace std;


unit::unit()
{

}

unit::unit(double X, double Y)
{
    health = 100;
    speed = 500;
    damage = 35;

    coordinate.x = X;
    coordinate.y = Y;

    unitMoveType = standartMove;
    sectorChange = 1000 / speed;
    countSectorChange = 0;

    keyRupture = false;
}

void unit::changeCoordinate(double X, double Y){
    coordinate.x += X;
    coordinate.y += Y;
}

bool unit::isSectorChange(){
    return sectorChange == countSectorChange;
}

bool unit::isRupture(){
    return keyRupture;
}

void unit::incrementCountSectorChange(){
    countSectorChange++;
}

void unit::clearCountSectorChange(){
    countSectorChange = 0;
}

void unit::setKeyRupture(bool rupture){
    keyRupture = rupture;
}

int unit::getSpeed(){
    return speed;
}

moveType unit::getMoveType(){
    return unitMoveType;
}

// Вывод координат в консоль (для отладки)
void unit::writeCoordinates(){
    cout << coordinate.x << " " << coordinate.y << "\n";
}

