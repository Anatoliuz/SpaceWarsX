#include "unit.h"
#include <iostream>
#include <math.h>

using namespace std;

//размер юнита(высота)
int unit::get_unit_height(){
    return height;
}

//размер юнита (ширина)
int unit::get_unit_width(){
    return width;
}

unit::unit()
{

}

coordinate_X_Y unit::get_unit_coordinates(){
    return coordinate;
}


unit::unit(double X, double Y, int planetNumber, int owner)
{
    static int unit_id = 0;
    owner_num = owner;
    
    unit_id++;
    internal_id = unit_id;
    health = 100;
    
    speed = 20;
    
    damage = 35;
    width = 15;
    height = 15;
    currentPlanet = planetNumber;
    transportationStatus = -1;
    change = round(900 / speed);
    countChange = 0;
    keyRupture = false;
    
    
    recharge = 100;
    countRecharge = 100;

    coordinate.x = X;
    coordinate.y = Y;
    unitAttackType = standartAttack;
    unitMoveType = standartMove;
    unitRibMoveType = standartRibMove;
}

bool unit::isChange(){
    return change == countChange;
}

bool unit::isRupture(){
    return keyRupture;
}

bool unit::isRecharge(){
    return recharge == countRecharge;
}

bool unit::isDead(){
    return health <= 0;
}

void unit::incrementCountChange(){
    countChange++;
}

void unit::clearCountChange(){
    countChange = 0;
}

void unit::incrementCountRecharge(){
    countRecharge++;
}

void unit::clearCountRecharge(){
    countRecharge = 0;
}

void unit::setCurrentPlanet(int planetNumber){
    currentPlanet = planetNumber;
}

void unit::setTransportationStatus(int status){
    transportationStatus = status;
}

void unit::setChange(int change){
    this->change = change;
}

void unit::setKeyRupture(bool rupture){
    keyRupture = rupture;
}

void unit::changeCoordinate(double X, double Y){
    coordinate.x += X;
    coordinate.y += Y;
}

void unit::takeDamage(int damage){
    health -= damage;
}

int unit::getHealth(){
    return health;
}

int unit::getSpeed(){
    return speed;
}

int unit::getDamage(){
    return damage;
}

int unit::getCurrentPlanet(){
    return currentPlanet;
}

int unit::getTransportationStatus(){
    return transportationStatus;
}

int unit::getChange(){
    return change;
}

coordinate_X_Y unit::getCoordinate(){
    return coordinate;
}

moveType unit::getMoveType(){
    return unitMoveType;
}

ribMoveType unit::getRibMoveType(){
    return unitRibMoveType;
}

attackType unit::getAttackType(){
    return unitAttackType;
}

// Вывод координат в консоль (для отладки)
void unit::writeCoordinates(){
    cout << coordinate.x << " " << coordinate.y << "\n";
}
int  unit::get_id(){
    return internal_id;
}

int unit::get_owner_num(){
    return owner_num;
}