#include "unit.h"
#include <iostream>


void unit::set_dt(float new_dt){
    dt = new_dt;
}
float unit::get_dt(){
    return dt;
}
coordinate_X_Y unit::get_unit_coordinates(){
    return coordinate;
}

unit::unit()
{

}

unit::unit(double X, double Y)
{
    width = 25;
    height = 50;
    health = 100;
    speed = 100;
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
    //cout << coordinate.x << " " << coordinate.y << "\n";
}

//размер юнита(высота)
int unit::get_unit_height(){
    return height;
}
//размер юнита (ширина)
int unit::get_unit_width(){
    return width;
}
